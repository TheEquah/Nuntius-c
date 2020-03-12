<!-- Author (Created): Roger "Equah" Hürzeler -->
<!-- Author (Modified): Roger "Equah" Hürzeler -->
<!-- Date (Created): 12020.01.05 HE -->
<!-- Date (Modified): 12020.03.12 HE -->
<!-- License: apache-2.0 -->

**Nuntius [C]**
================================================================================

[Nuntius](https://github.com/TheEquah/Nuntius/) C library implementation.

--------------------------------------------------------------------------------

# Architecture

Overview of the Nuntius architecture.

## Nuntius

Nuntius is a binary data serialization format. The data contains entries, which always start with an [SBLInt](https:github.com/TheEquah/SBLInt) indicating the element type, followed by binary data of the element.

## Interpreter

Nuntius data is interpreted. Elements interpret themselves by e.g. reading the next byte or given amount of bytes. This allows to implement element types containing data of fixed length, in data defined length, character terminated length or data streams.

## Element Type

All elements in Nuntius belong to a type. The element type defines an unique identity and functions how the Nuntius interpreter reads and writes the element. Note, that if an element type is not defined in a Nuntius document, that it will become unreadable.

### Identity

The identity of an element can be freely defined, which could also cause conflicts between applications using nuntius. It is important, that identity `0` should not be used.

--------------------------------------------------------------------------------

# Compile

To compile a C file with Nuntius, use the `#include "equah/nuntius.h"` at the beginning of the file.

The file can then be compiled by adding the `-I ./<path_to_src> -x c ./<path_to_src>/equah/nuntius.c` to the `gcc` command where `<path_to_src>` is the path to the [`/src/`](https://github.com/TheEquah/SBLInt-c/tree/master/src/) directory.

You also need the [SBLInt C](https://github.com/TheEquah/SBLInt-c/) library. SBLInt also needs the [SBSInt C](https://github.com/TheEquah/SBSInt-c/) library.

It will probably look something like `gcc -I ./Nuntius/lib/SBSInt-c/src -x c ./Nuntius/lib/SBSInt-c/src/equah/sbsint.c -I ./Nuntius/lib/SBLInt-c/src -x c ./Nuntius/lib/SBLInt-c/src/equah/sblint.c -I ./Nuntius/src -x c ./Nuntius/src/equah/nuntius.c -x c ./main.c -o ./main.o`.

## Requires

Nuntius requires the [SBLInt C](https://github.com/TheEquah/SBLInt-c/) library.

--------------------------------------------------------------------------------

# Examples

This repository provides the following examples for Nuntius.

## String

Example with a string element type.

Directory: [`/example/string/`](https://github.com/TheEquah/Nuntius-c/tree/master/example/string/)

--------------------------------------------------------------------------------
