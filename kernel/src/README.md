## How to set up a GDT

The GDT ("Global Descriptor Table") is a data structure used to define the different
memory areas: the base address, the size and access privileges like execute and write.
These memory areas are called "segments".

GDT layout

The GDT is a table divided in Segment (a logical contiguous chunck of memory), a Segment Register refers to a specific segment.

Segment
CS = Code Segment
DS = Data Segment
SS = Stack Segment
ES = Extra Segment
FS & GS = General Purpose Segment

Code segment is where you save your program (that runs the computer) whereas in data segment you save your data (that you want to be processed by a program)

Each Segment is filled with descriptors (hence Global Descriptor Table) which define characteristics of the Segment such as privilege/ring level, segment type, execution mode...

A Segment Seletor is reference (a pointer) to Segment Register

Segmentation vs Paging vs Flat memory model
Segmentation = Precisely and strictly defined chuncks of memory segments
Flat mode = memory appears to the program as a single contiguous address space. i.e. there is no distinction between each section of memory used, they all overlapp.
Paging = a memory management scheme by which a computer stores and retrieves data from secondary storage for use in main memory. In this scheme, the operating system retrieves data from secondary storage in same-size blocks called pages. In other words, instead of accessing directly the memory as in the flat model, programs access pages which defined the memory layout and its properties.

Real Mode vs Protected Mode
No hardware-based memory protection GDT in Real Mode, and exists between x+1000 and x+0800
Source: https://files.osdev.org/mirrors/geezer/os/pm.htm

Long Mode = 64bits
