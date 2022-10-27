# ELF

> elf - format of Executable and Linking Format (ELF) files
>
> -- <cite>man 5 elf</cite>

# Object files:

There are three main types of object files.
- A **relocatable** file holds code and data suitable for linking with other object files to create an
executable or a shared object file.
- An **executable** file holds a program suitable for execution.
- A **shared object** file holds code and data suitable for linking in two contexts. First, the link
  editor may process it with other relocatable and shared object files to create another object file.
  Second, the dynamic linker combines it with an executable file and other shared objects to
  create a process image.

Object files are binary representations of programs
intended to execute directly on a processor.

/*
              Linking...                              Executing...
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|            EFI Header             |    |            EFI Header             |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|  Program Header Table (Optional)  |    |       Program Header Table        |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|            Section 1              |    |            Segment 1              |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|              ...                  |    |            Segment 2              |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|           Section n               |    |              ...                  |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|              ...                  |    |              ...                  |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|              ...                  |    |              ...                  |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
|                                   |    |                                   |
|       Section Header Table        |    |  Section Header Table (Optional)  |
|                                   |    |                                   |
+-----------------------------------+    +-----------------------------------+
*/

A program header table, if present, tells the system how to create a process image. Files used
to build a process image (execute a program) must have a program header table; relocatable
files do not need one. A section header table contains information describing the file's sections.
Every section has an entry in the table; each entry gives information such as the section name,
the section size, and so on. Files used during linking must have a section header table; other
object files may or may not have one.


## ELF structure

There are 4 parts in an elf file:

- The elf header.
- The program header table.
- The section header table.
- The data referenced bz tables.

### ELF header (Ehdr)

**The ELF header is described by the type Elf32_Ehdr or Elf64_Ehdr:**

```c
#define EI_NIDENT 16

typedef struct {
   unsigned char e_ident[EI_NIDENT];
   uint16_t      e_type;
   uint16_t      e_machine;
   uint32_t      e_version;
   ElfN_Addr     e_entry;
   ElfN_Off      e_phoff;
   ElfN_Off      e_shoff;
   uint32_t      e_flags;
   uint16_t      e_ehsize;
   uint16_t      e_phentsize;
   uint16_t      e_phnum;
   uint16_t      e_shentsize;
   uint16_t      e_shnum;
   uint16_t      e_shstrndx;
} ElfN_Ehdr;

```