Having spent a couple of years writing python, almost exclusively, it's nice to
revisit another language and work in a completely different programming paradigm
with a fresh mindset, and the benefit of increased coding experience and wisdom*
(...age).

I had the opportunity to speak to some students at Hive about a project I'd
worked on while I was at the school, and present on how I'd approach the task
now as a 'pro' developer. What I chose to look at was my re-build of the
command-line program 'ls', which began my love affair with Unix.

It was a pretty eye-opening to read through that code I wrote back in 2022 once
again. Compared to what I'm producing now, which is by no means spectacular, it
was a total mess. Once I started rebuilding it in a more sensible fashion, I got
really into the project, and have ultimately spent most of my free time in the
last month re-implementing the entire program.

When I mentioned that I was working on a custom implementation of ls to some of
my more seasoned colleagues, after quizzing me on my motivations towards such an
endeavour, they'd pause for a few moments, gaze into the middle distance, maybe
scratch their heads, and ask:

"So... how does ls actually work?"

Let's explain through the medium of a demo MVP.

The simplest use-case of ls is just to run it without any arguments, and it
displays the contents of the current working directory.

// image of ls running without args

Now, this may at first seem quite straightforward. However, displaying these
file names across the terminal window in neatly aligned, lexicographically
sorted columns is surprisingly complicated. Perhaps that's a subject for another
article.

We'll skip that for now and create a version of ls that assumes the following options:

`-1` : print each file name, delimited by a newline character `'\n'`
`-a` : include file names that begin with a '.'
`-f` : do not sort the output

N.B. as always, you can RTFM for more info (`man ls`) // link to man page

// image of `ls -1 -a -f`

Step 1: Open a directory stream.

The purpose of our program is to print out the contents of the current working
directory. opendir(), followed by readdir() (called in a loop) provide us with
the core functionality of our program.

Before we get into the loop, let's open our stream and make sure we're correctly
error handling. Furthermore, if the stream opens successfully, we will need to
explicitly close it again when we're done (very few things happen implicitly in C,
and that, IMHO, is wonderful).

// image of opendir + error handling.

N.B. `man opendir` - you know the drill

I'm building this in the root of my recent project so that we actually have some
things to display. I have a test asset called `no_permission_soz` which is a
directory we cannot access (`chmod 0`). Altering our program slightly shows that we are
correctly handling `Permission denied` errors:

// images of error handling

Step 2: Read the directory stream

Now that we have successfully opened the stream of our current working
directory, we can examine the contents and loop through it like so:

// image of printing loop

Step 3: exploring lstat

However, the true power of ls is in the long format display (option `-l`), which
displays the chmod rwx permissions, size, link info and so on. For this demo,
let's just display the file size alongside each file name to give you a flavour
of what might come next.

N.B. `man 2 lstat`




What I've found particularly interesting about the experience of switching to C
again, is the different considerations that have to be made.

With python, I find myself thinking about the following things (this list is
extremely non-exhaustive):

- "Can I do this without creating another class"
- "Can I use a built-in, method, or list comprehension, rather than a for loop here"
- "How can I structure this project a little better to avoid import hell"

Furthermore, I find myself usually working against python's dynamic typing, rather than
with it...

C, on the other hand, presents a completely different array of considerations.
Firstly, the syntax of the language is a little harder to parse. For example, if
you are looking at a somewhat convoluted if condition involving bitwise
operations and derefencing memory addresses, it is extremely difficult to
quickly get a sense of what is being checked. I found myself abstracting away a
lot of that more esoteric syntax into a clearly named helper function.

For example, the program has to loop through the command-line arguments and
parse them. First, we need to determine if we are looking at an options arg, so
that said options can be applied.

(e.g. "-la", which would display the long format and include filenames begining
with '.' in the output)

So this:

```
if (!(arg[0] != '-' || ft_strequ(arg, "-"))
    break ;

```

becomes this:

```
static int  arg_is_options(char *arg)
{
    return (!(arg[0] != '-' || ft_strequ(arg, "-")));
}

...

if (!arg_is_options(arg))
    break ;
```

I don't need to examine, in detail, exactly how we determine whether the
given `arg` is an option arg or not, every time I read the code in this part of
the program. 99% of the time, knowing that we break out of the loop if we're not
looking at options at this point is good enough.

Side note: I've learnd the hard way to always use positive language when naming
custom boolean functions. `arg_is_not_option()` would more closely describe what
we actually need to check in this context. The problem is, it quickly leads to
confusing double-negatives when reading the code, e.g. "when it's not not an option,
we don't break". Furthermore, logically speaking, a negatively named function doesn't
really tell us anything meaningful about `arg` when it returns 'true', rather, it
just begs the question: "what is it then?"

The second major consideration I found myself making again and again while
working on this project, was trying to find ways to minimize the number of
system calls. C is an incredibly performant language, and iterates very quickly,
which is a blessing in a program like ls that sometimes needs to retrieve
large numbers of files from the system. The performance bottlenecks tend to be
found in situations involving a lot of back and forth between the program and
the system.

Let's look at an example of how I tackled this.

