# Hello, world
## C++ Edition

 So, you want to write a program in C++?
 
 You could ask your IDE (Visual Studio, Xcode, Eclipse, IDEA, etc.) to create you a simple starter project, but if you were asked—say, in a job interview—would you really be able to explain what’s going on?
 
 This tutorial will walk you through creating a simple terminal-based (“console-mode”, if you're on Windows) program, compiling and linking it properly, using version control and continuous integration, and working with different build systems.
 
 If you're working on macOS, Windows, or one of the more common Linux distributions, these instructions should work fine for you. If you're using a more esoteric distribution of Linux, or running a different Unix-based or Unix-like operating system (such as FreeBSD, Solaris, AIX, and so on), then _most_ of the instructions will work, but you'll have to make sure you already have a working C++ development environment, because this tutorial doesn't cover installing them on your platform.
 
### Our program

You'll need an editor that can create plain text files without trying to turn them into something else. Do **not** use a word processor (such as Word, Pages, or OpenOffice).

On Windows, Notepad is enough to get you started. You can use an IDE just for text editing if you have one installed, but it might be a bit heavyweight.

On macOS, you can use TextEdit, or `nano` in a Terminal.

On Linux and other Unix-like systems, you have an array of choices (depending upon your distribution and which packages you have installed), but if you're running GNOME then gEdit will do the job. If you're comfortable working in a terminal or on the console, than `nano` will do the job here, too, and will very probably be installed on your system already.

On Windows, macOS and Linux, you may find [Atom](https://atom.io) to be a good, free, GUI editor that you can use.
 
 Create a new folder to hold your "Hello, world" project—all of the files we create will be placed inside this folder. Unless you don't really have a choice, it's best to keep this folder on your local hard drive rather than on a USB stick, in Dropbox, or similar.
 
 Let's start with the C++ version of the classic "Hello, world" program:—
 
 ```cpp
#include <iostream>

int 
main(void)
{
	/* std::cout is a stream object bound to the 'standard output' file
	 * descriptor, which is where your normal output should be sent.
	 *
	 * Standard C++ stream objects override the << operator to provide a
	 * convenient syntax for writing to them.
	 */
	std::cout << "Hello, world!" << std::endl;
	
	/* The return value of main() is used as the program's exit status, which can
	 * be retrieved and checked by whatever program or script invoked yours: zero
	 * means it ran successfully, non-zero values mean an error occurred. It's up
	 * to you to define what those error codes might be used for. On many systems,
	 * negative exit statuses and values greater than 127 aren't guaranteed to
	 * work properly.
	 */
	return 0;
}
```

Using your text editor, create a new file containing the code above, and save it into your folder, naming it `hello.cc`.

You can name it something else if you prefer, but if you do you should remember:—

* The filename extension should be one of `cc`, `cxx` or `cpp`—many tools expect C++ source files to be named accordingly, and won't work properly by default unless they are.
* Wherever you see references to `hello.cc` elsewhere in the tutorial, substitute the name you chose.
* Wherever you see references to _different_ files which are named `hello` but have a different extension, you should change those to match the base name that you used.

	For example, if you chose to name your file `goodbye.cpp`, then replace any references to `hello.cc` with `goodbye.cpp`, and any other `hello` files (such as `hello.obj`) for `goodbye` instead, preserving whatever extension they used in the example.

### Building for the first time

People commonly refer to the entire process of turning some source code into an executable file that you can *run* as “compilation” or “compiling”, but that's not entirely accurate. The distinction isn't hugely important when you're working with a single source file, but when you have more complex projects—which you inevitably will—knowing how the whole _build process_ fits together becomes increasingly important.

#### Compilation

Strictly speaking, compilation is one step in the build process—translating (in our case C++) source into machine code in the form of an _object file_. An object file isn't your complete program: it still needs to be _linked_ (potentially with lots of other object files, as well as libraries) before it can become an executable.

Most C++ compilers actually perform three distinct steps, each of which can be invoked in isolation:

##### 1. Preprocessing

_Preprocessing_ is the process of scanning your source code, stripping out comments and extraneous whitespace, and dealing with _preprocessor directives_—things such as `#include` or `#define`. The result is a single, self-contained source file formatted in a particular way suitable for the compiler (although there are standards which specify how a preprocessor's output should look).

Like all build steps, preprocessing takes input in one format, and produces output in another: in this case, raw C++ source (along with any files that are `#include`d) is the input, and _preprocessed_ source is the output.

Unlike raw C++ source, which is generally portable between computers (and often between different platforms and architectures), preprocessed source will include the results of decisions, along with declarations, which are specific to your particular build environment. For this reason, the preprocessed source is usually just written to a temporary file before it's processed by the compiler proper, and deleted again afterwards.

The preprocessed source for our program generated by the Clang preprocessor on macOS might look like this:

```cpp
# 1 "hello.cc"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 373 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "hello.cc" 2
# 1 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/iostream" 1 3
# 37 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/iostream" 3
# 1 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/__config" 1 3
# 22 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/__config" 3
# 327 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/__config" 3
typedef __char16_t char16_t;
typedef __char32_t char32_t;

/* skip lots of <iostream> internals */

extern __attribute__ ((__visibility__("default"))) wostream wclog;

} }
# 2 "hello.cc" 2

int
main(void)
{






 std::cout << "Hello, world!" << std::endl;
# 21 "hello.cc"
 return 0;
}

```

The lines starting with `#` are instructions from the preprocessor to the compiler, telling it exactly where within the source files it has got to—this mainly allows the compiler to generate sensible diagnostic messages referring to the correct source files when it encounters a problem, as well as to generate debugging information that may be used later.

As you can see, the part of the program that _we_ wrote, at the bottom, is virtually identical to how it was written in our original source file. The key difference, besides comments being stripped out, is that the contents of the `<iostream>` header, along with any others that it itself includes, have all been merged together along with our source in order to produce a single self-contained output file that can be compiled.

It is possible to invoke _just_ the preprocessor and save the result (typically with a `.ii` extension for C++—e.g., `hello.ii` in our case)—this can be useful if you're trying to diagnose a problem with some complicated preprocessor macros or aren't sure that the correct files are being `#include`d.

Historically, C/C++ preprocessors have even been used to allow C/C++-style `#include` and macro processing to be used with other types of files entirely, although this practice can be quite error-prone and usually rely on a standalone purpose-built preprocessor instead nowadays.

##### 2. Compilation (proper)

The preprocessed source is passed to the compiler, which will generate _assembly language_ source. Assembly language source isn't _quite_ binary machine code, but is as close as it's reasonably possible for a compiler to get whilst still working with a text-based format.

Assembly language is made up of a combination of individual instructions that are executed by the processor, along with a small number of directives that provide additional information that is used later.

The precise nature of the assembly language output depends on quite a few factors, besides the contents of your source code: the architecture that you're building for, compiler flags (such as for debugging and optimisation), the version and brand of the compiler itself, the runtime libraries you're using, the operating system you're targeting, even the type of assembler you're using.

Usually, unless you're writing hand-optimised routines for a particular platform, you don't need to be able to read and understand the assembly language. As with the preprocessed C++ source, assembly language source (typically having a `.s` or `.asm` extension, depending upon the compiler and platform) will be written to a temporary file and deleted when compilation is complete unless you ask the compiler not to.

In the past, it wasn't uncommon for the assembler to ship with the operating system, but a compiler to come from a third-party vendor. This does still happen from time to time, but if you're targeting desktop or mainstream mobile platforms, you'll find that your development environment will include all of the tools in one place.

##### 3. Assembly

The job of assembly is performed by an _assembler_: it translates the textual assembly language source code into a binary form which is stored in object files.  The actual binary code within those object files is sometimes known as the _object code_. Don't confuse the word _object_ here with C++ object-oriented programming (OOP) concepts: at this level, it has nothing in particular to do with classes and instances, and just means “machine code that hasn't been linked to form a complete program”.

On most systems, object files will have an extension of `.o` or `.obj`. While you _can_ ask a compiler to produce an executable directly from your C++ source code, and it will discard the object files as it does the preprocessed source and assembly language output, this quickly becomes unweildy with larger projects consisting of a number of source files.

Keeping the object files around allows you to perform _incremental builds_, where you only re-compile the parts of the program which have changed since your last build. More on that later.

Let's compile our source to an object file.

##### macOS

On macOS, launch _Terminal_, which you can access by switching to Finder, pressing Cmd+Shift+U to open the _/Applications/Utilities_ folder, and double-clicking on the Terminal icon. A new window will open with a prompt ending in `$`, `>` or `%`, depending on your setup.

You should change directory inside the terminal to your project folder. To do this, you should type;

```
$ cd path/to/project
```

(Don't actually type the `$` sign, that's just a placeholder for the prompt you see in the Terminal).

The easiest way to do this, if you're not sure what the Unix-style path to your project folder is, is to type `cd` (followed by a space), and then drag your project folder from Finder into the Terminal window—Terminal will insert the full path of the folder for you, and you can just press _Return_.

Check that you're in the right place using the `ls` (list) command:

```
$ ls
hello.cc
```

In this case, we're in a directory containing one file, named `hello.cc`—exactly where we need to be. If you see something vastly different, go back and check what happened when you tried to `cd`, above.

You should now make sure you have the _macOS Command-line developer tools_ installed. These are generally worth installing on any power user's Mac, but virtually essential if you're a developer, whether or not you want to use Xcode. If you're not sure if you have them installed already, just type:—

```
$ xcode-select --install
```

If you don't have them installed, macOS will pop up a dialog box prompting you to download them, which will usually only take a couple of minutes. If you receive the following error:

```
$ xcode-select --install
xcode-select: error: command line tools are already installed, use "Software Update" to install updates
```

Then you're already good to go.

We'll use Clang, an open source compiler that's co-developed by Apple and incorporated into Xcode, to compile our program:—

```
$ c++ -W -Wall -c -o hello.o hello.cc
```

Step by step, this says:

1. Run `c++`: the de facto standard name on Unix systems for the C++ compiler; on macOS, this runs Clang’s C++ compiler.
2. `-W` and `-Wall` are Clang options that say "enable compiler warnings across various categories". The precise warnings which are enabled by these two options varies between versions, but they usually enable most of the warnings you might want the compiler to give you, and none of the ones which are matters of archaic style. You should virtually never work without warnings enabled (if the compiler's warning about something that you know definitely isn't a problem, you should adjust your code to silence the warning rather than telling the compiler not to produce that warning at all)
3. The `-c` option tells the compiler to produce an object file rather than an executable. While it's a handy convenience that the compiler will by default attempt to turn a source file into a ready-to-run program, understanding the relationship between the compiler, object files, and the linker is essential to being able to manage your projects properly.
4. The `-o hello.o` option specifies the name of the object file that the compiler should create. In our case, it will be called `hello.o`.
5. Finally, we specify the name of the source file—`hello.cc`. The compiler will preprocess, compile, and assemble this file for us. If we were to for some reason specify some ready-preprocessed source instead, e.g. `hello.ii`, then the compiler would skip the preprocessing step. Similarly, if we provided assembly language source, the compiler would skip preprocessing _and_ compilation and move straight to the assembly phase of producing the object file.

Assuming the macOS Command-line developer tools were properly installed, and you definitely are in the correct directory, this command should look a lot like it did absolutely nothing—that's because Unix commands work on a principle of only producing output when they _need_ to; you can tell the compilation was successful because the compiler _didn't_ tell you that it wasn't. You can check with `ls` again:

```
$ ls
hello.cc hello.o
```

We now have two files: our source code, in `hello.cc`, and our object code, in `hello.o`.

##### Windows


#### Linking

Once the compiler has done its job and turned your C++ source code into an object file, that object file can be _linked_ to produce a program that you can actually run. This is the job of a _linker_.

A linker takes several inputs: combinations of object files and _libraries_ (which are just collections of related object files distributed together) and arranges them in order to produce a single binary file that can be executed. On Windows, this will usually have an extension of `.exe`, while on macOS and other Unix-like platforms, executables aren't usually given an extension at all.

Even if your source code consists of a single file, it's extremely rare that you're writing an entirely self-contained program. For example, in our `hello.cc`, we use the `std::cout` instance, which is some kind of `std::ostream`.

On macOS (or Linux and similar), we can invoke the linker by hand to try to create an executable from our object file:

```
$ ld -o hello-cpp hello.o
ld: warning: No version-min specified on command line
Undefined symbols for architecture x86_64:
  "__Unwind_Resume", referenced from:
      __ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_ in hello.o
      __ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m in hello.o
      __ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_ in hello.o
  "__ZNKSt3__16locale9use_facetERNS0_2idE", referenced from:
      __ZNSt3__14endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_ in hello.o
      __ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m in hello.o
[ lots of errors trimmed ]
```

Those "undefined symbols" are all for things related to `std::basic_ostream`, the class which `std::cout` is an instance of. There isn't much point in having a C++ development environment if we have to implement all of the standard classes ourselves—so where are they and how do we use them?

The answer is the _runtime libraries_, often also referred to as the _standard libraries_ (although to be strictly correct, only those runtime libraries which implement a particular standardised environment should be called standard libraries!)

The set of runtime libraries you use are specific to the combination of architecture, operating system and programming language that you're working with.

Perhaps confusingly, the most appropriate way to invoke the linker is not directly, as above, but to ask the compiler to do it for us. Instead of supplying it with some C++ source, if we provide a C++ compiler with object files (that were compiled from C++ source).

Other languages work similarly: if you're working with Objective-C, you need to ask the Objective-C compiler to invoke the linker for you. Writing software in multiple languages (each compiling to object code, and then being linked together) _is_ possible, but can quickly become complicated when different sets of runtime libraries need to be involved.

The fact that compiler spends a lot of its time running _other_ programs is why the people who actually develop compilers will refer to the tool you call "the compiler" as a compiler _driver_, and structure it such that the only thing it does is invoke one or more other programs (of which the "real" compiler is just one, alongside a preprocessor, assembler and linker), passing the output from one step as the input of the next.

Generally, however, unless you need to be specific, you can use the following terminology:

* A _compiler_ translates source code into object files.
* A _linker_, usually invoked _via_ the compiler, combines object files and libraries to produce an executable.
* A _preprocessor_ is usually invoked automatically by the compiler in order to do its job, and produces a preprocessed version of your source code.
* An _assembler_ is usually invoked automatically by the compiler in order to do its job, and produces an object file from the assembly language that the compiler generates.

Let's ask the C compiler to link our C++ program.

##### macOS and Linux

Back in your _Terminal_, run the following:

```
$ c++ -o hello-cpp hello.o
```

From the description of the compilation step, you should be able to decipher this command.

Once again, this will be silent if it was successful, so let's check with `ls` again:

```
$ ls
hello-cpp hello.cc  hello.o
```

We've produced a new file—`hello-cpp`, from our object file. Let's run it:

```
$ ./hello-cpp
Hello, world!
```

Success!

##### Windows

### Version control

Now we've built our program for the first time—and successfully run it—let's enable version control for our project.

For this example, we'll use Git as our version control system, and Github for repository hosting. There are a great many books, cheat-sheets and tutorials for both out there, which this tutorial wouldn't hope to replicate.

We'll do several things:

* Turn our project directory in a version-controlled repository
* Make sure that certain types of files that we don't care about don't _pollute_ the repository
* Create a repository on Github where we'll keep a publicly-visible copy of our code
* Commit an initial version of our program and push the changes to Github
* Modify our program, compile, link, and run it, examine the differences using Git, and finally commit and push our updated version.

#### Enable version control

```
$ git init
Initialized empty Git repository in /Users/me/hello/.git/
```

#### Decide which files to exclude ("ignores")

```
$ cat >.gitignore << EOF
/hello-cpp
*.exe
*.o
*.s
*.i
*.ii
*.bc
*.obj
*.lib
*.log
*.out
*.run
*.pid
EOF
```

#### Create a Github repository

#### Commit and push

#### Make some changes

