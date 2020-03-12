// Author (Created): Roger "Equah" Hürzeler
// Author (Modified): Roger "Equah" Hürzeler
// Date (Created): 12020.01.08 HE
// Date (Modified): 12020.03.12 HE
// License: apache-2.0


#ifndef equah_nuntius__HEADER
#define equah_nuntius__HEADER


// [>] Identity Type
// [i] Datatype to use for element identity.
// [NOTE] This should be the same as the SBLInt integer type.
#define equah_nuntius__IDENTITY_TYPE unsigned int


#include <stddef.h>
#include <stdio.h>

#include "equah/sblint.h"


// [i] Define types.
typedef struct equah_nuntius__Interpreter_ equah_nuntius__Interpreter;
typedef struct equah_nuntius__Element_Type_ equah_nuntius__Element_Type;
typedef struct equah_nuntius__Element_ equah_nuntius__Element;
typedef struct equah_nuntius__Interface_ equah_nuntius__Interface;


// [>] Interpreter
// [i] Struct providing functions to interpret Nuntius.
struct equah_nuntius__Interpreter_ {
	
	// [>] Interface
	// [i] Pointer to interface to read and write Nuntius.
	equah_nuntius__Interface *interface;
	
	// [>] Element Types
	// [i] Pointer to array containing pointers to interpretable element types.
	equah_nuntius__Element_Type **element_types;
	
	// [>] Element Types - Length
	// [i] Amountof available indexes for element types.
	size_t element_types__len;
	
	// [>] Element Types - Position
	// [i] The next empty index to write new element types.
	size_t element_types__pos;
	
};

// [>] Element Type
// [i] Struct used to interpret a type of element.
struct equah_nuntius__Element_Type_ {
	
	// [>] Identity
	// [i] The identifyer of this element.
	equah_nuntius__IDENTITY_TYPE identity;
	
	// [>] Read
	// [i] Read function of this element. Executed when this element sould read it's data.
	size_t (*fn_read)(equah_nuntius__Element *, equah_nuntius__Interpreter *);
	
	// [>] Write
	// [i] Write function when his element should write it's data.
	size_t (*fn_write)(equah_nuntius__Element *, equah_nuntius__Interpreter *);
	
	// [>] Data
	// [i] Void pointer to store any additionally required data for this element to read and write.
	void *data;
	
};

// [>] Element
// [i] Struct to represent data of an element.
struct equah_nuntius__Element_ {
	
	// [>] Interpreter
	// [i] Interpreter related to this element.
	equah_nuntius__Element_Type *type;
	
	// [>] Data
	// [i] Void pointer where this element can store data.
	void *data;
	
};

// [>] Interface
// [i] Struct providing functions to read nuntius input.
struct equah_nuntius__Interface_ {
	
	// [>] Read Available
	// [i] Positive number if read possible.
	size_t (*fn_read_available)(equah_nuntius__Interface *);
	
	// [>] Read
	// [i] Read bytes from input.
	size_t (*fn_read)(equah_nuntius__Interface *, unsigned char *, size_t);
	
	// [>] Read Single
	// [i] Read single byte.
	unsigned char (*fn_read_single)(equah_nuntius__Interface *);
	
	// [>] Write Available
	// [i] Positive number if write is possible.
	size_t (*fn_write_available)(equah_nuntius__Interface *);
	
	// [>] Write
	// [i] Write given bytes to output.
	size_t (*fn_write)(equah_nuntius__Interface *, const unsigned char *, size_t);
	
	// [>] Write Single
	// [i] Writes single byte.
	void (*fn_write_single)(equah_nuntius__Interface *, unsigned const char);
	
};


// [i] Function declarations.
void equah_nuntius__Interpreter__init(equah_nuntius__Interpreter *);
size_t equah_nuntius__Interpreter__register_element_type(equah_nuntius__Interpreter *, equah_nuntius__Element_Type *);
equah_nuntius__Element_Type *equah_nuntius__Interpreter__get_element_type(equah_nuntius__Interpreter *, equah_nuntius__IDENTITY_TYPE);
size_t equah_nuntius__Interpreter__write_element(equah_nuntius__Interpreter *, equah_nuntius__Element *);
size_t equah_nuntius__Interpreter__read_element(equah_nuntius__Interpreter *, equah_nuntius__Element *);


#endif
