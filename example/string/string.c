// Author (Created): Roger "Equah" Hürzeler
// Date (Created): 12020.03.12 HE
// License: apache-2.0


#include <stdio.h>
#include <string.h>

#include "equah/nuntius.h"


// [>] My Interface.
// [i] This creates an example interface using a char array.
unsigned char io[1024];
size_t io_pos = 0;
size_t io_len = 1024;
size_t fn_read_available(equah_nuntius__Interface *interface) {
	return io_len - io_pos - 1;
}
size_t fn_read(equah_nuntius__Interface *interface, unsigned char *buff, size_t r_len) {
	size_t pos = 0;
	while (interface->fn_read_available(interface) && r_len > pos) {
		buff[pos] = io[io_pos];
		io_pos++;
		pos++;
	}
	return pos;
}
unsigned char fn_read_single(equah_nuntius__Interface *interface) {
	unsigned char c = io[io_pos];
	io_pos++;
	return c;
}
size_t fn_write_available(equah_nuntius__Interface *interface) {
	return io_len - io_pos - 1;
}
size_t fn_write(equah_nuntius__Interface *interface, const unsigned char *buff, size_t w_len) {
	size_t pos = 0;
	while (interface->fn_read_available(interface) && w_len > pos) {
		io[io_pos] = buff[pos];
		io_pos++;
		pos++;
	}
	return pos;
}
void fn_write_single(equah_nuntius__Interface *interface, unsigned const char c) {
	io[io_pos] = c;
	io_pos++;
}
equah_nuntius__Interface my_interface = {
	.fn_read_available = &fn_read_available,
	.fn_read = &fn_read,
	.fn_read_single = &fn_read_single,
	.fn_write_available = &fn_write_available,
	.fn_write = &fn_write,
	.fn_write_single = &fn_write_single
};

// [>] (Nuntius Element) String - Read
// [i] Function called to read element data.
size_t ne_string__read(equah_nuntius__Element *element, equah_nuntius__Interpreter *interpreter) {
	
	size_t pos = 0;
	char next = 0x00;
	
	do {
		next = interpreter->interface->fn_read_single(interpreter->interface);
		((char *) element->data)[pos] = next;
		pos++;
	} while (next != 0x00);
	
	return pos;
}

// [>] (Nuntius Element) String - Write
// [i] Function called to write element data.
size_t ne_string__write(equah_nuntius__Element *element, equah_nuntius__Interpreter *interpreter) {
	
	size_t pos = 0;
	do {
		interpreter->interface->fn_write(interpreter->interface, ((char *) element->data) + pos, 1);
		pos++;
	} while (interpreter->interface->fn_write_available(interpreter->interface) && ((char *) element->data)[pos] != 0x00);
	
	if (interpreter->interface->fn_write_available(interpreter->interface)) {
		interpreter->interface->fn_write(interpreter->interface, ((char *) element->data) + pos, 1);
		pos++;
	}
	
	return pos;
}

// [>] (Nuntius Element) String
// [i] The null terminated string element.
equah_nuntius__Element_Type ne_string = {
	.identity = 1,
	.fn_read = &ne_string__read,
	.fn_write = &ne_string__write,
	.data = NULL
};

// [>] Main
int main() {
	
	printf("\n");
	
	// [i] Create nuntius interpreter.
	equah_nuntius__Element_Type *my_interpreter__element_types[100];
	equah_nuntius__Interpreter my_interpreter;
	equah_nuntius__Interpreter__init(&my_interpreter);
	my_interpreter.interface = &my_interface;
	my_interpreter.element_types__len = 100;
	my_interpreter.element_types = my_interpreter__element_types;
	
	// [i] Register string element in interpreter.
	equah_nuntius__Interpreter__register_element_type(&my_interpreter, &ne_string);
	
	// [i] Create a string element instance.
	char string1_data[512] = {0};
	strcpy(string1_data, "Hello World");
	equah_nuntius__Element string1 = {
		.type = &ne_string,
		.data = string1_data
	};
	
	// [i] Create a second string element.
	char string2_data[512] = {0};
	strcpy(string2_data, "This is my second string.");
	equah_nuntius__Element string2 = {
		.type = &ne_string,
		.data = string2_data
	};
	
	// [i] Write both string elements with interface.
	size_t string1_written = equah_nuntius__Interpreter__write_element(&my_interpreter, &string1);
	printf("\nFirst element written: \"%s\" (%li bytes)", string1.data, string1_written);
	size_t string2_written = equah_nuntius__Interpreter__write_element(&my_interpreter, &string2);
	printf("\nSecond element written: \"%s\" (%li bytes)", string2.data, string2_written);
	
	// [i] Print content currently in io.
	printf("\n\nIO: ");
	size_t pos_pr = 0;
	while (io_len >= pos_pr) {
		printf("0x%x; ", (unsigned char) io[pos_pr]);
		pos_pr++;
	}
	printf("\n");
	
	// [i] Create empty element to store read data.
	char elemin_data[1024] = {0};
	equah_nuntius__Element elemin = {
		.data = elemin_data
	};
	
	// [i] Reset interface position.
	io_pos = 0;
	
	// [i] Read first element and print data.
	equah_nuntius__Interpreter__read_element(&my_interpreter, &elemin);
	printf("\n(ID: %li) DATA: \"%s\"", elemin.type->identity, elemin.data);
	
	// [i] Reuse elemin to read second element and print data.
	equah_nuntius__Interpreter__read_element(&my_interpreter, &elemin);
	printf("\n(ID: %li) DATA: \"%s\"", elemin.type->identity, elemin.data);
	
	printf("\n\n");
	
	return 0;
}
