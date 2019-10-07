# Bash, Integration Testing and Unit Testing

> Author(s): Brian Crites ([@brrcrites](https://github.com/brrcrites)), Rachid Ouit

In this lab you will learn the basics of how to use bash (Bourne Again SHell) scripting to automate common tasks and improve your workflow, as well as how that can be leveraged to create basic integration tests for CLI (command line interface) programs. Bash is a perfect language when you need to automate a small task on the command line and the cost of building the same script in a higher level language is higher than the task itself. While bash is usually used to automate small tasks, there are lots of systems that are built on top of it or use it as part of their running process. These include many of the UNIX commands you are familiar with as well as many major build and package management systems.

## Basic Shell Script

> Note: Bash will be executable on most UNIX and Mac systems, however does not natively work with Windows. The easiest way to do this lab on a Windows machine is either to ssh into the Hammer server and run it there, or to install the Ubuntu Subsystem for Windows, which is available in the app store for Windows 10.

First, you should clone this repository and perform the rest of the lab within that clone. This lab will point out good places to commit your changes as an example, however future labs will not have these hints. The TA will grade your last commit to this repository before the deadline.

We're going to start with the basics, creating a hello world bash script that you can execute on the command line. Start by opening a new `hello.sh` file in your editor of choice and writing the following:

```shell
#!/bin/sh

echo "hello world"
```

The first line `#!/bin/sh` is used to tell the system that the file we are writing should be an input to another program. The `#!` symbols (known as a shebang or hashbang) notes that this program should be used as an executable, and the `/bin/sh` is the executable the rest of the code should be sent to. In this case, it is the path to the bash executable. The rest of the code is the basic [echo](http://www.linfo.org/echo.html) command, which prints the next strip back to standard output.

Now, save the file and try and execute it from the command line:

```
$ ./hello.sh
```

You should get an error like the following, `-bash: ./hello.sh: Permission denied`. This has to do with the permissions that files are given by default in UNIX environments, and is essentially a security feature to stop you from accidentally executing files. In order to make the file executable, we have to chmod (change mode) the file, where in this case the mode is readable, writing, executable and by who, owner, group, or all. Run an `ls -l` and you should be able to see the current mode for all the files in this directory.

```
$ ls -l
total 16
-rw-r--r--  1 user  staff  2669 Sep 13 12:42 README.md
-rw-r--r--  1 user  staff    30 Sep 13 12:39 hello.sh
```

The left three characters are the owner mode, the middle three are the group mode, and the last three are for everyone who isn't the owner for in the group. You can read more about the nuances of [chmod here](https://ss64.com/bash/chmod.html), but right now we are going to focus on making the file executable. In order to add the executable (`x`) attribute to a file, we can use the `+x` shorthand in the following way:

```
chmod +x hello.sh
```

Now, try executing the file again using `./hello.sh` and you should see `hello world` print out to your console. Congratulations, you've created your first bash script. The most important things to remember from this section are the shebang line that starts your bash script (`#!/bin/sh`) and how to make your script executable (`chmod +x <file>`).

> Make a commit here with the hello.sh file

## Bash Arrays and Loops


```c++
#include <iostream>

int main(int argv, char** argc) {
    // Skip the first argc index because its the program
    for(int i = 1; i < argv; i++) {
        std::cout << argc[i] << " ";
    }
    std::cout << std::endl;
}
```

Compile this program as `c-echo` (`g++ c-echo.cpp -o c-echo`) and test it with some different inputs to verify that it prints whatever is passed to it as an input parameter. Now, let's create a program named `array.sh` which can automatically run this program with some known inputs to automate it's testing.

```shell
#!/bin/sh

INPUTS=("first input" "second input" "third input")

./c-echo ${INPUTS[2]}
./c-echo ${INPUTS[1]}
./c-echo ${INPUTS[0]}
```

Let's dig into the top line (after the shebang). Variables are declared the same way in bash as they are in C++ with an equals sign (`=`), and its common to have global variables names written in all capital letters like in C++. Here we are declaring a bash style array with three values. Note that the array has parentheses (`()`) surrounding all its values, and that the values are separated by spaces rather than commas. Because the values are separated by spaces and not commas, its common to surround the values in quotes. Without the quotes above the array would have six values instead of three.

When you run this script, you should see that it prints out the inputs (in reverse order) and nothing else. What is happening is that the `INPUT[i]` is being replaced by the i'th indexed array value. The dollar sign and curly bracket syntax (`${INPUTS[i]}`) are used to tell bash that this is a variable and not a string literal. All variables that you use in your bash should be surrounded by the dollar sign and curly brackets (`${VAR}`). So the following lines

```
./c-echo ${INPUTS[2]}
./c-echo ${INPUTS[1]}
./c-echo ${INPUTS[0]}
```

Are replaced instead with the values from the array, and the following is executed instead

```
./c-echo third input
./c-echo second input
./c-echo first input
```

Because this will simply execute the code, it is often common to have the system echo out what it is going to run before running it. This makes it easier for the user of the script to understand what is going on and what they should expect to be output. Update your script to the following:

```shell
#!/bin/sh

INPUTS=("first input" "second input" "third input")

echo "Executing ./c-echo ${INPUTS[2]}"
./c-echo ${INPUTS[2]}
echo "Executing ./c-echo ${INPUTS[1]}"
./c-echo ${INPUTS[1]}
echo "Executing ./c-echo ${INPUTS[0]}"
./c-echo ${INPUTS[0]}
```

> Make a commit here with the c-echo.cpp and array.sh files, **as well as a .gitignore file that includes the c-echo executable**

Obviously if we have a large array, or multiple arrays where we want to iterate to run all combinations, then hand coding the combinations is less than desirable. Luckily bash supports various types of loops including iteration loops. Lets try and replace our hard coded execution lines with a loop instead. Update your array.sh file with the following:

```shell
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    ./c-echo ${input}
done
```

Make sure to take careful note of the quotes around the inputs array (`"${INPUTS[@]}"`), and lets take a closer look at that line. The line is structured as `for x in y` where `x` is the variable that `y` will be unpacked into. In the case of bash for loops it supports in-line lists, so if you put a single value for `y` it will do a single iteration replaced the variable `x` with `y`. Alternatively you could have put multiple values separated by spaces in place of the `y` and `x` would iterate over all of them. We've already discussed that we need the dollar sign and curly braces (`${}`) to tell bash that this is a variable and not a literal, but lets look at the index of operator with ampersand (`[@]`). This expands the array inputs into its constituent parts, and without it the for loop would only iterate over the first element in the array. 

The last thing we need to consider is why we need the extra quotes around the `INPUTS` variable, which has to do with the way shell replaces and parses values. When bash sees the variable symbols (`${}`) it replaces that variable with the value, which in the case of the first iteration would be `first input`. The problem we now have is with the for loop, since this type of loop allows for a list of comma separated values to be put in-line when the variable is replaced with two different values it will try and iterate over them separatly and each word in the array will be run separatly. When we add the quotes the loop then sees these two words as a single entry (which is what we want) and will execute it correctly. These little details can make bash a bit difficult to work with at first, but will become more natural the more you work with it (and Stack Overflow is your friend).

As for the loop itself, it starts with the `for` keyword, but must be followed with a `do` keyword on the next line (or separated from the `for` line with a semicolon (`;`), which represents a newline. Everything after the `do` keyword makes up the loop body, and will be executed each iteration, until we reach the `done` keyword, which represents the end of the loop body.

Loop iterations are not only useful for user defined arrays, but are also useful for iterating over data that bash interprets as array. For instance, you can easily iterate over a directory of files like you would when you need to process multiple files through a program and didn't want to do it one file at a time. Create a new file, `list.sh`, with the following code:

```shell
for file in ./*
do
    echo $(basename "$file")
done
```

Here, the `./*` piece of the for loop returns all the files (using the wildcard character `*`) at the directory path `./` which is the local directory. The `$(basename "$file")` calls the [basename command](http://pubs.opengroup.org/onlinepubs/007908799/xcu/basename.html) within bash, replace the input to the command with the iteration variable. The basename command strips out the path from a file path leaving only the file name.

> Make a commit here with the list.sh file

## Bash If and Else

Loops make it easy for us to iterate over a set of files to bulk process data or to run a number of different inputs through a program, but we'll need conditionals if we want to validate output or run only a subset of files from a directory for process. Lets open our `array.sh` file and update it to make sure that the output of our program matches what we expect.

```shell
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
```

The first thing we do differently here is we run the command using the bash command syntax that we used when we ran the basename command earlier. This executes the command and saves the result to the variable `output`. Next, we have our if statement which starts with the `if` keyword and then has a condition to evaluate within square brackets (`[]`). The square brackets are actually a shorthand for a conditional test in bash, and will always return a true or false value (which is very convenient when working with if/else). Next we have the `then` keyword, which like `do` in the loop represents the start of the loop body. We then have what we want the condition to execute if the condition is met, follow by and `else` keyword and what we want the condition to execute if its false. Finally, the entire condition body is ended with the `fi` keyword (`if` backwards) in the same way that `done` ends the loop body.

Now, let's run this code and take a look at the output. You should see something like the following:

```
./c-echo first input
Test failed
./c-echo second input
Test failed
./c-echo third input
Test failed
```

Looks like our outputs didn't match out inputs, why could that be? Let's take a closer look at the output we get and what we compare it to and see if we can find the issue. Rewrite the `array.sh` script to print both values **surrounded by string literals**.

```shell
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    echo "Output: \"${output}\""
    echo "Input: \"${input}\""
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
```

Run the updated test code and the issue should be fairly obvious. Out c-echo program prints a space after every word in `argc`, leading to a trailing whitespace that doesn't exist in the input. Let's go ahead and update the c-echo program so that we skip printing the trailing whitespace.

```c++
#include <iostream>

int main(int argv, char** argc) {
    // Skip the first argc index because its the program
    for(int i = 1; i < argv; i++) {
        std::cout << argc[i];
        // Print a whitespace after all but the last iteration
        if(i < argv - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
```

Now, re-compile the program (remember to use `g++ c-echo.cpp -o c-echo` so it generates the correct executable) and re-run your `array.sh` test script. It should now say that all the tests have been passed.

> Make a commit here with the assay.sh and c-echo.cpp files

## Bash for Integration/System Testing

When creating a bash script to execute a command line program and check the resulting output we are performing a basic version of integration and system testing. The bash script mimics the way a user would enter commands into the CLI, making it very effective at testing the program interface, and by leveraging conditionals it can report back to us if the resulting output matches what we are expecting. In the example we went through above there is only a single function, so we have essentially written a method for performing integration, system, and unit testing all at the same time because with such as small example they are all essentially  the same. Even if we add more components in the form of classes and functions within the program, bash will only ever execute the program through the `main()` function putting it squarely into the realm of integration and system testing. Using loops and other more advanced bash features such as [command line arguments](http://linuxcommand.org/lc3_wss0120.php), [user input](https://ryanstutorials.net/bash-scripting-tutorial/bash-input.php), and [functions](https://ryanstutorials.net/bash-scripting-tutorial/bash-functions.php) makes it fairly easily to create a basic but reliable and extendable integration testing system for CLI programs.

## Unit Testing in C++

The type of testing that we've been doing so far is what's known as "black-box testing", because we don't need to know anything about the internal workings of the system in order to test it. This could also be considered an integration test, because were testing all the modules of the systems integrated together instead of each module individually. This stands in contrast to a unit test, which tests each module (class, function, etc.) individually and doesn't test how these modules interact. The example we have done here could be considered both a unit test and an integration test because it is a single module that we are testing, but you can see how if we added more modules into the main then the testing we are doing would be integration, since we would have no way to test those modules individually from the command line.

Testing is a very important part of the software development process that is often overlooked in university curriculum. We know because **Google told us specifically it was something they found lacking in their incoming interns and new grad hires**, so we suggest you take this unit seriously along with the testing you will be doing for your projects (and add it to your resume when you apply for internships).

Because C++ is a compiled language, it is fairly difficult to create unit tests for individual classes and functions because they need a main to perform the test running. Rather than try and invent our own testing paradigms/frameworks, we are going to use the fairly standard [Google Unit Test Framework](https://github.com/google/googletest) (gtest) for C++. While it's tempting to think we are using this because Google told us we needed more testing in the curriculum, it is actually because the author ([@brrcrites](https://github.com/brrcrites)) uses it in his research, and it has become the de-facto standard testing framework for C++ code.

Since we are going to write unit tests for this program, we first want to break the project up into different modules so it's easier to test. Note that for this small example we will only be creating a single function as our module for testing, but the principles are the same if you have a single module or hundreds. Lets modify our c-echo.cpp file, and rename it to c-echo.h. If we rename and then modify c-echo.cpp without telling git that we are going to rename it, then it's going to think we removed one file and created an entirely new one. This can make the commits very hard to read (and review very difficult), so we should rename the file using git itself:

```
$ git mv c-echo.cpp c-echo.h
```

If you run `git status` you should see that git has logged the file rename. Now, lets turn c-echo.h into a function rather than just a main:

```c++
#include <iostream>

std::string echo(int length, char** chars) {
    std::string ret = "";
    for(int i = 1; i < length; i++) {
        ret += chars[i];
        if(i < length - 1) {
            ret += " ";
        }
    }
    ret += "\n";
    return ret;
}
```

Notice that now instead of printing directly, we are generating a string which we will print to standard output in the main. Now, let's create a new main.cpp file so we can run the program like we did before:

```c++
#include "c-echo.h"

int main(int argv, char** argc) {
    std::cout << echo(argv, argc);
}
```

One of the benefits of writing unit tests is that it forces you to think about how to subdivide a problem across a number of different classes and functions, because those become your testable units. 

## CMake

Before we can start actually writing the unit tests, there are a few changes we'll need to make to our repository. The first issue is that in order to use gtest is we'll need to change from hand compiling our program to using a build system. Gtest doesn't support the basic make build system, but instead supports [CMake](https://cmake.org/) which is a build system built on top of make and supports some more advanced features. The CMake system looks for a CMakeLists.txt file in order to know what to build, so start by creating the following CMakeLists.txt file:

```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(c-echo
    main.cpp
)
```

The first function, `CMAKE_MINIMUM_REQUIRED`, sets the minimum version of CMake that can be used to compile this program. The function `ADD_EXECUTABLE` tells CMake to create a new exectuable named after the first parameter in that function, in this case `c-echo`. We then list all the `.cpp` files which need to be included in that executable. In this case we only have the main.cpp, which has a `#include` for the c-echo.h file which makes sure that the c-echo.h file gets included during compilation (this has to do with the way that C++ compilers stitch some files together during compilation, and won't be further covered in this lab). I mentioned earlier that CMake is built on top of make, and to be more specific what it does is actually generate really good make files. Run the following command from the terminal in order to generate a new make file to compile your program:

```
$ cmake3 .
```

This command envokes the cmake build system in the local directory (where our CMakeLists.txt file is located). **Make sure you use the `cmake3` comamnd and not just `cmake`**. Hammer has two version of cmake installed, and if you do not use the `cmake3` command you will get an error (note that you will likely just use the `cmake` command when you develop on your local environment, since you will only have one version of CMake installed). This will then generate a Makefile that matches the executable that we asked for in our CMakeLists.txt. Go ahead and envoke the Makefile and you should see a nicely designed build percentage which will generate a new `c-echo` executable.

```
$ make
[ 50%] Building CXX object CMakeFiles/c-echo.dir/main.cpp.o
[100%] Linking CXX executable c-echo
[100%] Built target c-echo
```

Now that we've switched the build system, go ahead and run a few test commands on the new executable and re-run your array.sh file to make sure its still functioning as we expected. Since we made what could be a major breaking change to the program, its a good idea to make sure we test the changes to make sure its still working as expected before we make any new changes. We should also update our .gitignore file to ignore the generated build files:

```
CMakeCache.txt
CMakeFiles/
cmake_install.cmake
Makefile

c-echo
```

Now that we have a function that we can create unit tests for specifically, and can use CMake to build it, we can now add the gtest framework and start writing our tests.

> Make a commit here with CMakeLists.txt, c-echo.h, main.cpp, and the updated .gitignore.

## Git Submodules

We could download the gtest source code and include it in our git repository, but the gtest code is already has its own open source repository on GitHub. Instead of creating copies of the gtest framework everywhere with no easy way to keep track of version, git has a mechanism for including code from other git repositories in your own known as submodules. In order to include the gtest framework as a submodule, you'll first need to [find the clone link for the respoitory from their GitHub repository](https://github.com/google/googletest) and then use the `git submodule` command to add it as a submodule to the system.

```
$ git submodule add https://github.com/google/googletest.git
```

This will create a new googletest folder which contains all the code from the gtest repository. If you run `git status` you should also see that the googletest folder has already been added for commiting, as well as a hidden .gitmodules file, which has the information for which submodules this repository should contain. 

> Note: when we add the googletest repository as a submodule it automatically downloads the source code to our local machine, but adds a link to the repository in GitHub. If you download a project containing a submodule from GitHub (which you will likely do at some point for your assignment) you will need to add a `--recursive` flag to your `git clone` command to pull the submodule along with the repository (`git clone --recursive <github-repo-url>`). If you forget to pull recursively and need to pull the submodule after cloning you can use the command `git submodule update --init --recursive` within the newly clone repository to pull any missing submodules.

Now we need to modify our CMakeLists.txt file so it knows to compile the gtest code along with our own code by adding the following:

```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(c-echo
    main.cpp
)

ADD_EXECUTABLE(test
    test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
```

These changes do a few things for us. The first is the `ADD_SUBDIRECTORY` function, which makes CMake aware of the gtest framework. It will then look into that directory for another CMakeLists.txt file which will tell it how to compile that code and include it in our own. Next we have a `SET` function, which we use to set the C++ standard that we want to compile against to C++11. This is essentially equivalent to adding a `-std=c++11` flag to your g++ compilation. We also have a new `ADD_EXECUTABLE` line which requires a new test.cpp file. This test.cpp file is where we will write our tests and create a main specifically for running those tests. This new executable will just run the tests and won't run the normal program functionality, so we still need the old executable to be generated. Finally, we add a `TARGET_LINK_LIBRARIES` function, which links our test program to the gtest library, making gtest a dependency for the test executable (note that the name *gtest* is actually defined by the Google Unit Test Framework, not by us). Finally, we have a `TARGET_COMPILE_DEFINITIONS` function, which adds a compilation definition to the build, which in this case disables googletest from looking for the pthreads library which hammer doesn't have. This is equivalent to adding a `-Dgtest_disable_pthreads=ON` flag which is a compiler pre-processor option. If you are doing this lab on you local machine,  you may be able to remove this last line of the CMakeLists.txt file.

## Writing a Unit Test

Now, lets create the test.cpp file and create our first unit test:

```c++
#include "c-echo.h"

#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

We start by including our c-echo.h so we have access to the `echo` function that we want to test, and we also `#include` the gtest framework. The gtest inclusion doesn't reference the gtest.h file from the directory directly, but instead uses a special gtest/ directory which we have access to through the `TARGET_LINK_LIBRARIES` function in the CMake (notice it matches the gtest from that command). 

After that we create our first unit test. There are lots of different types of tests that you can create using the gtest framework, and I suggest you read this [quick introduction to gtest guide](https://www.ibm.com/developerworks/aix/library/au-googletestingframework.html), and then reference this [gtest primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md) when you are looking for something more specific, in addition to the google test official documentation. The first test is defined with the `TEST` function, which takes a test set name (`EchoTest`) and a name for this specific test (`HelloWorld`). All tests with the same test set name will be grouped together in the output when the tests are run. In this test, we create a `char** test_val` with three values, which is the executable `./c-echo` followed by `hello world`. Remember that our function is programmed to skip the executable, so in order to test it properly we still need to pass the executable to the function. Finally, we create a new main which runs all the tests that we have written (this main is given in the documentation and you are unlikely to need to change it). 

Now that we've modified our CMakeLists.txt, we'll need to generate a new Makefile before we can compile the tests. Run the following commands to generate a new Makefile, compile the new targets, and then run the tests:

```
$ cmake3 .
$ make
$ ./test
```

When you run the tests, you should see an output like the following:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from EchoTest
[ RUN      ] EchoTest.HelloWorld
.../test.cpp:8: Failure
Expected equality of these values:
  "hello world"
  echo(3,test_val)
    Which is: "hello world\n"
[  FAILED  ] EchoTest.HelloWorld (0 ms)
[----------] 1 test from EchoTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] EchoTest.HelloWorld

 1 FAILED TEST
```

Oops, we failed our first test. Lets take a look at the output and try and see why.

```
Expected equality of these values:
  "hello world"
  echo(3,test_val)
    Which is: "hello world\n"
```

The problem is that we expected `hello world` to be returned, but we forgot that the function actually adds a newline to the end of the string so the prompt will go to the next line. At this point we have two options (1) if we actually want the function to return `hello world`, we need to modify the function or (2) if the function should actually return a newline then we need to change the test. In a test driven design methodology, we would actually write one or a small number of basic unit tests, then develop a small part of our system until we pass those unit tests, and then repeat that process until we've finish our function (and then we already have our unit tests). Here, the function echo should probably directly mimic the input so we don't actually want that newline in the function but instead in the main. Go ahead and modify the function in c-echo.h so it no longer returns the newline and instead add that newline to the main.cpp, and re-run the test to make sure you are now passing (since the tests don't run the other main, the added newline there won't be a problem for testing), you should see something like this:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from EchoTest
[ RUN      ] EchoTest.HelloWorld
[       OK ] EchoTest.HelloWorld (0 ms)
[----------] 1 test from EchoTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

> Make a commit here with the CMakeLists.txt, main.cpp, test.cpp, and c-echo.h file as well as the googletest and .gitmodules files

## Testing Edge Cases

The first test you've written represents the type of average case we would expect from the user, which are important to test. You also want to make sure you are testing edge cases, where the functionality of what you are testing may not be as obvious. For example, our echo function is designed to mimic exactly what is input so a blank input gets a blank response. Another developer may assume that no input is invalid and return some type of error. Lets create a unit test for an empty input, which tests that is equivalent to returning a blank.

```c++
TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo";
    EXPECT_EQ("", echo(1,test_val));
}
```

This new test makes two valuable additions to our system. The first is if another developer modifies the functionality of our echo function to do anything on a blank input except return nothing (throw an error for example) then they will fail the test and have to consciously make the decision about changing to test to match the function, or changing the function to meet the test (as you did earlier). The second thing we gain is the usage of tests as a form of documentation. If I am wondering what the result of zero input to the function is, I can check the tests and assuming there is a test with that edge case I can see what result the tests expects. In this way a comprehensive set of tests is its own form of documentation (although you should consider this a supplement form of documentation, not a replacement for actual documentation).

## Submission

Create three test cases in addition to the two we've already created, and commit it all to your repository as your submission.

