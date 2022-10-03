# ELF

> elf - format of Executable and Linking Format (ELF) files
>
> -- <cite>man 5 elf</cite>

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