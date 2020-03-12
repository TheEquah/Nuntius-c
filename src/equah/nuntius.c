// Author (Created): Roger "Equah" Hürzeler
// Author (Modified): Roger "Equah" Hürzeler
// Date (Created): 12020.01.08 HE
// Date (Modified): 12020.03.12 HE
// License: apache-2.0


#include "equah/nuntius.h"


// [>] Interpreter - Initialize
// [i] Sets empty interpreter values.
// [P] interpreter {equah_nuntius__Interpreter *} => Interpreter to initialize.
void equah_nuntius__Interpreter__init(equah_nuntius__Interpreter *interpreter) {
	
	// [i] Set empty values.
	interpreter->interface = NULL;
	interpreter->element_types = NULL;
	interpreter->element_types__len = 0;
	interpreter->element_types__pos = 0;
	
}

// [>] Interpreter - Register Element Type
// [i] Adds an element type to the interpreter.
// [P] interpreter {equah_nuntius__Interpreter *} => Interpreter to which to add this element.
// [P] type {equah_nuntius__Element_Type *} => Type to add to element types.
// [R] {size_t} Position at which the type is indexed.
size_t equah_nuntius__Interpreter__register_element_type(equah_nuntius__Interpreter *interpreter, equah_nuntius__Element_Type *type) {
	
	interpreter->element_types[interpreter->element_types__pos] = type;
	interpreter->element_types__pos++;
	
	return interpreter->element_types__pos;
}

// [>] Interpreter - Get Element Type
// [i] Search for the given element type by identity.
// [P] interpreter {equah_nuntius__Interpreter *} => Interpreter to search types in.
// [P] identity {equah_nuntius__IDENTITY_TYPE} => Identity of the element type to search.
// [R] {equah_nuntius__Element_Type *} Ponter to element type of given id or NULL pointer if the identity was not found.
equah_nuntius__Element_Type *equah_nuntius__Interpreter__get_element_type(equah_nuntius__Interpreter *interpreter, equah_nuntius__IDENTITY_TYPE identity) {
	
	for (size_t pos = 0; pos < interpreter->element_types__pos; pos++) {
		if (interpreter->element_types[pos]->identity == identity) {
			return interpreter->element_types[pos];
		}
	}
	
	return NULL;
}

// [>] Interpreter - Write Element
// [i] Writes identity and data of the given element to the interface output.
// [P] interpreter {equah_nuntius__Interpreter *} => Interpreter to write element with.
// [P] element {equah_nuntius__Element *} => Element to write.
// [R] {size_t} => Amount of bytes written.
size_t equah_nuntius__Interpreter__write_element(equah_nuntius__Interpreter *interpreter, equah_nuntius__Element *element) {
	
	// [>] Write Single
	// [i] Function to write a single character for SBLInt.
	// [P] c {unsigned const char} => Character to write over interface.
	void write_single(unsigned const char c) {
		interpreter->interface->fn_write_single(interpreter->interface, c);
	}
	
	size_t size = 0;
	
	if (interpreter->interface->fn_write_available(interpreter->interface)) {
		
		// [i] Write type identity.
		size += equah_sblint__int_to_sbytes(element->type->identity, &write_single);
		
		// [i] Write element data.
		size += element->type->fn_write(element, interpreter);
		
	}
	
	return size;
}

// [>] Interpreter - Read Element
// [i] Reads identity and data of the next element of the interface input.
// [P] interpreter {equah_nuntius__Interpreter *} => Interpreter to read with.
// [P] element {equah_nuntius__Element *} => Element to store read data in.
// [R] {size_t} Amount of read bytes.
size_t equah_nuntius__Interpreter__read_element(equah_nuntius__Interpreter *interpreter, equah_nuntius__Element *element) {
	
	// [>] Read Single
	// [i] Function to reas single character for SBLInt.
	// [R] {unsigned char} => Next characterread from input.
	unsigned char read_single() {
		return interpreter->interface->fn_read_single(interpreter->interface);
	}
	
	size_t size = 0;
	
	if (interpreter->interface->fn_read_available(interpreter->interface)) {
		
		// [i] Read type identity.
		equah_nuntius__IDENTITY_TYPE identity = 0;
		size += equah_sblint__sbytes_to_int(&read_single, &identity);
		
		// [i] Get element type and read data if type was found.
		element->type = equah_nuntius__Interpreter__get_element_type(interpreter, identity);
		if (element->type != NULL) {
			size += element->type->fn_read(element, interpreter);
		}
		
	}
	
	
	return size;
}

