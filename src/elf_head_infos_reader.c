//
// Created by Hajar Sabir on 10/4/22.
//

#include "nm.h"
#include "const_defines.h"

static char	*get_target_arch(t_data *data)
{
	switch (data->mmap_ptr[EI_OSABI]) {
		case 0x00:
			return "System V";
		case 0x01:
			return "HP-UX";
		case 0x02:
			return "NetBSD";
		case 0x03:
			return "Linux";
		case 0x04:
			return "GNU Hurd";
		case 0x05:
			return "Solaris";
		case 0x07:
			return "AIX (Monterey)";
		case 0x08:
			return "IRX";
		case 0x09:
			return "FreeBSD";
		case 0x0A:
			return "Tru64";
		case 0x0B:
			return "Novell Modesto ";
		case 0x0C:
			return "OpenBSD";
		case 0x0D:
			return "OpenVMS";
		case 0x0E:
			return "NonStop Kernel";
		case 0x0F:
			return "AROS";
		case 0x10:
			return "FenixOS";
		case 0x11:
			return "Nuxi CloudABI";
		case 0x12:
			return "Stratus Technologies OpenVOS";
	}
	return "Target arch not found";
}

static char *get_e_type(t_data *data)
{
	switch (data->mmap_ptr[E_TYPE]) {
		case 0x00:
			return "NONE, Unknown.";
		case 0x01:
			return "REL, Relocatable file.";
		case 0x02:
			return "EXEC, Executable file.";
		case 0x03:
			return "DYN, Shared object (Position-Independent Executable file).";
		case 0x04:
			return "CORE, Core file.";
	}
	return "E_TYPE: Not found";
}

static char *get_machine_instr_arch(t_data *data)
{
	switch (data->mmap_ptr[E_MACHINE]) {
		case 0x00:
			return "No specific instruction set";
		case 0x01:
			return "AT&T WE 32100";
		case 0x02:
			return "SPARC ";
		case 0x03:
			return "x86";
		case 0x04:
			return "Motorola 68000 (M68k) ";
		case 0x05:
			return "Motorola 88000 (M88k) ";
		case 0x06:
			return "Intel MCU ";
		case 0x07:
			return "Intel 80860 ";
		case 0x08:
			return "MIPS";
		case 0x09:
			return "IBM System/370 ";
		case 0x0A:
			return "MIPS RS3000 Little-endian ";
		case 0x0E:
			return "Hewlett-Packard PA-RISC ";
		case 0x13:
			return "Intel 80960 ";
		case 0x14:
			return "PowerPC ";
		case 0x15:
			return "PowerPC (64-bit) ";
		case 0x16:
			return "S390, including S390x ";
		case 0x17:
			return "IBM SPU/SPC ";
		case 0x24:
			return "NEC V800 ";
		case 0x25:
			return "Fujitsu FR20 ";
		case 0x26:
			return "TRW RH-32 ";
		case 0x27:
			return "Motorola RCE ";
		case 0x28:
			return "Arm (up to Armv7/Aarch32) ";
		case 0x29:
			return "Digital Alpha ";
		case 0x2A:
			return "SuperH ";
		case 0x2B:
			return "SPARC Version 9 ";
		case 0x2C:
			return "Siemens TriCore embedded processor ";
		case 0x2D:
			return "Argonaut RISC Core ";
		case 0x2E:
			return "Hitachi H8/300 ";
		case 0x2F:
			return "Hitachi H8/300H ";
		case 0x30:
			return "Hitachi H8S ";
		case 0x31:
			return "Hitachi H8/500 ";
		case 0x3E:
			return "AMD x86-64 ";
	}
	return "Machine Instruction Set Arch: Not found";
}

int	read_elf_hdr(t_data *data)
{
	ft_printf(0, "----ELF MAGIC----\n");
	ft_printf(0, "1. 0x%x\n", data->mmap_ptr[EI_MAG0]);
	ft_printf(0, "2. 0x%x\n", data->mmap_ptr[EI_MAG1]);
	ft_printf(0, "3. 0x%x\n", data->mmap_ptr[EI_MAG2]);
	ft_printf(0, "4. 0x%x\n", data->mmap_ptr[EI_MAG3]);
	ft_printf(0, "----Arch----\n");
	if (data->mmap_ptr[EI_CLASS] == 1)
		ft_printf(0, "- 32-bit\n");
	else
		ft_printf(0, "- 64-bit\n");
	ft_printf(0, "----Target Arch----\n");
	ft_printf(0, "- %s\n", get_target_arch(data));
	ft_printf(0, "----Endian----\n");
	if (data->mmap_ptr[EI_DATA] == ELFCLASS32)
		ft_printf(0, "- little\n");
	else
		ft_printf(0, "- big\n");
	ft_printf(0, "\n----E Type----\n");
	ft_printf(0, "- Object type: %s\n", get_e_type(data));
	ft_printf(0, "\n----Machine Instruction Set Arch----\n");
	ft_printf(0, "- %s\n", get_machine_instr_arch(data));


	return 0;
}