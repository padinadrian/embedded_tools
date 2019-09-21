/**
 * File:    examplePS2.ino
 * Author:  padin.adrian@gmail.com
 *
 * Copyright 2019
 */

/*
    This file is necessary to include the
    adrian_dualshock.cpp file in the examplePS2 sketch.

    Sadly Arduino doesn't play well with outside CPP files,
    but it does automatically compile every INO file in the
    same directory as the main sketch file, hence this
    workaround.
*/

/* ===== Includes ===== */
#include "C:\\Users\\apadi\\Documents\\projects\\n64_dualshock/embedded_tools/ps2/adrian_dualshock.cpp"
