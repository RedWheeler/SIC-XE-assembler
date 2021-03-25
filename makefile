driver:: Instruction_Factory.o \
	Object_Program.o \
	Format4_Instruction.o \
	Format3_Instruction.o \
	Format2_Instruction.o \
	Format1_Instruction.o \
	Word.o \
	Byte.o \
	RSUB.o \
	utilities.o\
	driver.cpp
		g++ Instruction_Factory.o \
		Object_Program.o \
		Format4_Instruction.o \
		Format3_Instruction.o \
		Format2_Instruction.o \
		Format1_Instruction.o \
		Word.o \
		Byte.o \
		RSUB.o \
		utilities.o \
		driver.cpp -o driver

Object_Program.o:: Object_Program.cpp Object_Program.h
	g++ -c Object_Program.cpp

Instruction_Factory.o:: Instruction_Factory.cpp Instruction_Factory.h
	g++ -c Instruction_Factory.cpp 

Format4_Instruction.o:: Format4_Instruction.cpp Format4_Instruction.h
	g++ -c Format4_Instruction.cpp

Format3_Instruction.o:: Format3_Instruction.cpp Format3_Instruction.h
	g++ -c Format3_Instruction.cpp

Format2_Instruction.o:: Format2_Instruction.cpp Format2_Instruction.h
	g++ -c Format2_Instruction.cpp

Format1_Instruction.o:: Format1_Instruction.cpp Format1_Instruction.h
	g++ -c Format1_Instruction.cpp

Word.o:: Word.cpp Word.h
	g++ -c Word.cpp

Byte.o:: Byte.cpp Byte.h
	g++ -c Byte.cpp

RSUB.o:: RSUB.cpp RSUB.h
	g++ -c RSUB.cpp

utilities.0:: utilities.cpp utilities.h
	g++ -c utilities.cpp
clean::
	rm *.o
	rm driver
