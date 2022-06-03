/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Campo_jpg;
    const int            Campo_jpgSize = 313834;

    extern const char*   KnobCapr2_png;
    const int            KnobCapr2_pngSize = 478443;

    extern const char*   KnobCaprHW3_png;
    const int            KnobCaprHW3_pngSize = 346974;

    extern const char*   Legno_jpg;
    const int            Legno_jpgSize = 294840;

    extern const char*   LOGO_Capr_png;
    const int            LOGO_Capr_pngSize = 1712519;

    extern const char*   RuotaCarro2_png;
    const int            RuotaCarro2_pngSize = 421044;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
