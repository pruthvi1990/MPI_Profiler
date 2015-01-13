wrap.py
===========================
a [PMPI](http://www.open-mpi.org/faq/?category=perftools#PMPI) wrapper generator

by Todd Gamblin, tgamblin@llnl.gov, https://github.com/tgamblin/wrap

    Usage: wrap.py [-fgd] [-i pmpi_init] [-c mpicc_name] [-o file] wrapper.w [...]
     Python script for creating PMPI wrappers. Roughly follows the syntax of
       the Argonne PMPI wrapper generator, with some enhancements.
     Options:"
       -d             Just dump function declarations parsed out of mpi.h
       -f             Generate fortran wrappers in addition to C wrappers.
       -g             Generate reentry guards around wrapper functions.
       -c exe         Provide name of MPI compiler (for parsing mpi.h).
                      Default is \'mpicc\'.
       -s             Skip writing #includes, #defines, and other
                      front-matter (for non-C output).
       -i pmpi_init   Specify proper binding for the fortran pmpi_init
                      function.  Default is \'pmpi_init_\'.  Wrappers
                      compiled for PIC will guess the right binding
                      automatically (use -DPIC when you compile dynamic
                      libs).
       -o file        Send output to a file instead of stdout.


Thanks to these people for their suggestions and contributions:

* David Lecomber, Allinea
* Barry Rountree, LLNL

Known Bugs:

* Certain fortran bindings need some bugfixes and may not work.

Tutorial
-----------------------------
For a thorough tutorial, look at `examples/tutorial.w`!  It walks you through
the process of using `wrap.py`.  It is also legal `wrap.py` code, so you
can run `wrap.py` on it and see the output to better understand what's
going on.


CMake Integration
-----------------------------
`wrap.py` includes a `WrapConfig.cmake` file.  You can use this in your CMake project to automatically generate rules to generate wrap.py code.

Here's an example.  Suppose you put `wrap.py` in a subdirectory of your project called wrap, and your project looks like this:

    project/
        CMakeLists.txt
        wrap/
            wrap.py
            WrapConfig.cmake
In your top-level CMakeLists.txt file, you can now do this:

    # wrap.py setup -- grab the add_wrapped_file macro.
    set(WRAP ${PROJECT_SOURCE_DIR}/wrap/wrap.py)
    include(wrap/WrapConfig.cmake)

If you have a wrapped source file, you can use the wrapper auto-generation like this:

    add_wrapped_file(wrappers.C wrappers.w)
    add_library(tool_library wrappers.C)

The `add_wrapped_file` function takes care of the dependences and code generation for you.  If you need fortran support, call it like this:

    add_wrapped_file(wrappers.C wrappers.w -f)

And note that if you generate a header that your .C files depend on, you need to explicitly include it in a target's sources, unlike non-generated headers.  e.g.:

    add_wrapped_file(my-header.h my-header.w)
    add_library(tool_library
        tool.C         # say that this includes my-header.h
        my-header.h)   # you need to add my-header.h here.

If you don't do this, then the header dependence won't be accounted for when tool.C is built.

Wrapper file syntax
-----------------------------
Wrap syntax is a superset of the syntax defined in Appendix C of
the MPE manual [1], but many commands from the original wrapper
generator are now deprecated.


The following two macros generate skeleton wrappers and allow
delegation via `{{callfn}}`:

* `fn` iterates over only the listed
functions.
* `fnall` iterates over all functions *minus* the named functions.

    {{fnall <iterator variable name> <function A> <function b> ... }}
      // code here
    {{endfnall}}

    {{fn <iterator variable name> <function A> <function B> ... }}
    {{endfn}

    {{callfn}}

`callfn` expands to the call of the function being profiled.

`fnall` defines a wrapper to be used on all functions except the functions named.  fn is identical to fnall except that it only generates wrappers for functions named explicitly.

    {{fn FOO MPI_Abort}}
    	// Do-nothing wrapper for {{FOO}}
    {{endfn}}

generates (in part):

    /* ================== C Wrappers for MPI_Abort ================== */
    _EXTERN_C_ int PMPI_Abort(MPI_Comm arg_0, int arg_1);
    _EXTERN_C_ int MPI_Abort(MPI_Comm arg_0, int arg_1) {
        int return_val = 0;

    // Do-nothing wrapper for MPI_Abort
        return return_val;
    }

`foreachfn` and `forallfn` are the counterparts of `fn` and `fnall`, but they don't generate the
skeletons (and therefore you can't delegate with `{{callfn}}`).  However, you
can use things like `fn_name` (or `foo`) and `argTypeList`, `retType`, `argList`, etc.

They're not designed for making wrappers, but declarations of lots of variables and other things you need to declare per MPI function.  e.g., say you wanted a static variable per MPI call for some flag.

    {{forallfn <iterator variable name> <function A> <function B> ... }}
      // code here
    {{endforallfn}

    {foreachfn <iterator variable name> <function A> <function B> ... }}
      // code here
    {{endforeachfn}}


The code between {{forallfn}} and {{endforallfn}} is copied once
for every function profiled, except for the functions listed.
For example:

    {{forallfn fn_name}}
      static int {{fn_name}}_ncalls_{{fileno}};
    {{endforallfn}}

might expand to:

    static int MPI_Send_ncalls_1;
    static int MPI_Recv_ncalls_1;
    ...

etc.

* `{{get_arg <argnum>}}` OR `{{<argnum>}}`
	Arguments to the function being profiled may be referenced by
	number, starting with 0 and increasing.  e.g., in a wrapper file:

        void process_argc_and_argv(int *argc, char ***argv) {
        // do stuff to argc and argv.
        }

        {{fn fn_name MPI_Init}}
            process_argc_and_argv({{0}}, {{1}});
        {{callfn}}
        {{endfn}}
    Note that `{{0}}` is just a synonym for `{{get_arg 0}}`

* `{{ret_val}}`
	ReturnVal expands to the variable that is used to hold the return
	value of the function being profiled.   (was: `{{returnVal}}`)

* `{{fn_num}}`
	This is a number, starting from zero.  It is incremented every time
	it is used.

* `{{ret_type}}`
	The return type of the function. (was: `{{retType}}`)

* `{{formals}}`
	Essentially what would be in a formal declaration for the function.
	Can be used this with forallfn and foreachfn; these don't generate
	prototypes, they just iterate over the functions without making a
    skeleton.  (was: `{{argTypeList}}`)

* `{{args}}`
	Names of the arguments in a comma-separated list, e.g.:
    `buf, type, count, comm`

* `{{argList}}`
	Same as `{{args}}`, but with parentheses around the list, e.g.:
    `(buf, type, count, comm)`

* `{{applyToType <type> <callable>}}`
    This macro must be nested inside either a fn or fnall block.
    Within the functions being wrapped by fn or fnall, this macro will
    apply `<callable>` to any arguments of the function with type
    `<type>`.   For example, you might write a wrapper file like this:

        #define my_macro(comm) do_something_to(comm);
        {{fn fn_name MPI_Send MPI_Isend MPI_Ibsend}}
            {{applyToType MPI_Comm my_macro}}
            {{callfn}}
        {{endfn}}

Now the generated wrappers to `MPI_Send`, `MPI_Isend`, and `MPI_Ibsend` will do something like this:

    int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) {
      int _wrap_py_return_val = 0;
      my_macro(comm);
      PMPI_Isend(buf, count, datatype, dest, tag, comm, request);
    }

* `{{sub <new_string> <old_string> <regexp> <substitution>}}`
    Declares `<new_string>` in the current scope and gives it the value
    of `<old_string>` with all instances of `<regexp>` replaced with
    `<substitution>`.  You may use any valid python regexp for `<regexp>`
    and any valid substitution value for `<substitution>`.  The regexps
    follow the same syntax as Python's re.sub(), and they may be single
    or double quoted (though it's not necessary unless you use spaces in
    the expressions).

    Example:

        {{forallfn foo}}
            {{sub nqjfoo foo '^MPI_' NQJ_}}
            {{nqjfoo}}
        {{endforallfn}}

  This will print `NQJ_xxx` instead of `MPI_xxx` for each MPI function.

* `{{fileno}}`
	An integral index representing which wrapper file the macro
	came from.  This is useful when decalring file-global variables
	to prevent name collisions.  Identifiers declared outside
	functions should end with _{{fileno}}.  For example:

		static double overhead_time_{{fileno}};

	might expand to

		static double overhead_time_0;


* `{{vardecl <type> <arg> <arg> ...}}` *(not yet supported)*
	Declare variables within a wrapper definition.  Wrap will decorate
    the variable name to prevent collisions.

* `{{<varname>}}` *(not yet supported)*
	Access a variable declared by `{{vardecl}}`.

#MPI Profiler to generate the task Graph and to calculate the Critical Path

##Creating a Profiler

The way you create the profiler is by using the PMPI layer. Essentially, MPI is designed in such a way that
each MPI function is defined as a weak symbol. That means that all MPI functions have an implementation
within the MPI library. However, if you, the programmer, override that implementation by creating your
own version of the MPI function, your version will instead be invoked. The existing MPI library version of
the calls simply invokes a function by the same name except there is a “P” before it. For example, if the
user invokes MPI Barrier(MPI COMM WORLD), the MPI library implementation of this function looks
as follows:

MPI_Barrier(MPI_COMM_WORLD) {
PMPI_Barrier(MPI_COMM_WORLD);
}

All the “real” code that implements a barrier is within PMPI Barrier. This allows you to override
MPI Barrier as follows:
MPI_Barrier(MPI_COMM_WORLD) {
Pre_MPI() // you probably want to pass in an MPI opcode here
PMPI_Barrier(MPI_COMM_WORLD);
Post_MPI() // you probably want to pass in an MPI opcode here
}

For example, one thing one might do within your version of MPI Barrier is add one to a counter, so you
can keep the total number of barriers executed.
To provide a generic wrapper that will intercept all functions, please use Todd Gamblin’s MPI wrapper
generator (not required if you really feel like you need to implement this yourself, but recommended). See
https://github.com/tgamblin/wrap for details.

##MPI Task Graph

During execution of the MPI program, you need to generate an MPI task graph. Below, we define terms and
explain how to do this. An MPI task graph is a directed, weighted graph with the following attributes:
 There is one vertex corresponding to each invoked MPI operation (if an MPI operation is invoked
n times, there will be n vertices for that MPI operation).

1. There is an edge between every pair of consecutive vertices v and w, and the edge weight is the wallclock
time that has elapsed from the end of the MPI operation corresponding to v and the beginning
of the MPI operation corresponding to w.
2. If the MPI operation is an MPI Send or MPI Isend, then there is also an edge from vertex v (where
v corresponds to the MPI Send or MPI Isend) to a vertex z, which is the matching MPI Recv or
MPI Wait call, with weight equal to the message latency. Assume all MPI Send operations do not
block, and assume that an MPI rank never sends to itself.
3. To estimate the message latency, you are to run a series of benchmarks that will generate a function
that takes as input a message size (when necessary) and returns the associated message latency. This
experiment requires just two nodes for point-to-point messages. For the point-to-point experiments,
set up a program that takes as input a message size and then has rank 0 send to rank 1 a message of
that size and then receive a message (from rank 1) of that size. Rank 1 performs those actions in the
opposite order (first receive, then send). This “ping-pong” should be done a large number of times.
The message latency is then the total time divided by the number of repetitions, divided by 2 (since
we are estimating one-way latency). Perform this experiment for many different message sizes, e.g.,
4 bytes, 8 bytes, 16 bytes, : : :, 32K bytes. Take the series of (byte, time) pairs and perform a linear
regression to get the function you need. Software packages such as Excel, Google Spreadsheet, and
R can do the regression. Note that for the collectives, your regression will have two independent
variables. (Also, you should execute all the collectives, as MPI Alltoall has a different latency
than a barrier.)
4.  There must be a single vertex representing each of MPI Init and MPI Finalize, with appropriate
edges to the first operation on each rank (for MPI Init) and edges from the last operation on each
rank (for MPI Finalize).
5. For collectives (specifically, MPI Barrier, MPI Alltoall, MPI Scatter, MPI Gather,
MPI Reduce, and MPI Allreduce), you should have one vertex with a fan-in and fan-out (see
Figure 1). Note that this is not actually correct for most of the collectives, but we are making a
simplifying assumption. For all collectives, the (vertex) weight should be the based on your regression
function for that collective.
6. Also, convert MPI Waitall into multiple equivalent calls to MPI Wait.

##Critical Path

>After program execution (at MPI Finalize), the MPI critical path graph should then be displayed on the
screen, and, you must save the critical path itself to a file in the following strict format: (1) each vertex
must contain the MPI function name with the exact capitalization and punctuation conventions used in MPI
itself, followed by one blank space and then the rank; (2) for each edge, (a) if it is a computation edge, the
integer value (rounded), or (b) if it is a latency edge, the number of total bytes in the message. Separate all
fields by one blank space. For MPI Init, MPI Finalize, and any collective, use -1 for the rank. Please
output this into the file critPath.out. Figure 2 has an example task graph and corresponding output to
be placed in critPath.out. Note that the send-receive edges have the number of bytes in parentheses.
For on-screen display, you should use the “DOT” tool (see: http://www.graphviz.org/, along
with the “Cluster” example at http://www.graphviz.org/Gallery/directed/cluster.html

