// This file is released under the 3-clause BSD license. See COPYING-BSD.

function builder_gw_cpp()

//    includes_src_c = ilib_include_flag(get_absolute_file_path("builder_gateway_cpp.sce") + "../../src/c");
//
//    //adapt to compiler capabilities
//    l = ilib_language();
//    if ~isempty(grep(l, "cppsci")) then
//        tbx_build_gateway("skeleton_cpp", ..
//            ["cpp_find","sci_cpp_find", "csci"; ..
//            "cpp_error", "sci_cpperror", "cppsci"; ..
//            "cpp_foo", "sci_cppfoo", "cppsci"; ..
//            "cpp_sum", "sci_cppsum", "cppsci"; ..
//            "cpp_sub", "sci_cppsub", "cppsci"; ..
//            "cpp_multiplybypi", "sci_cppmultiplybypi", "cppsci"], ..
//            ["sci_cpp_find.cxx", "sci_cpperror.cpp", "sci_cppfoo.cpp", "sci_cppsum.cpp", "sci_cppsub.cpp", "sci_cppmultiplybypi.cpp"], ..
//            get_absolute_file_path("builder_gateway_cpp.sce"), ..
//            ["../../src/c/libcsum"], ..
//            "", ..
//            includes_src_c);
//    else
//        tbx_build_gateway("skeleton_cpp", ..
//            ["cpp_find","sci_cpp_find", "csci"], ..
//            ["sci_cpp_find.cxx"], ..
//            get_absolute_file_path("builder_gateway_cpp.sce"), ..
//            ["../../src/c/libcsum"], ..
//            "", ..
//            includes_src_c);
//    end
    gw_cpp_path = get_absolute_file_path('builder_gateway_cpp.sce');

    gw_cpp_files = findfiles(gw_cpp_path, '*.cpp');
    scifunctions_name = gw_cpp_files(grep(gw_cpp_files, 'sci_'));
    scifunctions_name = strsubst(scifunctions_name, 'sci_', '');
    scifunctions_name = strsubst(scifunctions_name, 'percent', '%');
    scifunctions_name = strsubst(scifunctions_name, '.cpp', '');

    cppfunctions_name = gw_cpp_files(grep(gw_cpp_files,'sci_'));
    cppfunctions_name = strsubst(cppfunctions_name, '.cpp', '');

    gw_tables = [scifunctions_name, cppfunctions_name];

    mqtt_libs = [];
    inter_ldflags = "";
    inter_cflags = "";

    PAHO_INCLUDE_ROOT_PATH = fullpath(gw_cpp_path + "../../thirdparty/paho/windows/include");
    inter_cflags = ilib_include_flag([PAHO_INCLUDE_ROOT_PATH]);

//    INCLUDE_ROOT_PATH = fullpath(gw_cpp_path + "../../thirdparty/ArtemisDLL/include");
//    //    OPENCV_INCLUDE = fullpath(OPENCV_INCLUDE_ROOT_PATH + "/opencv");
//    //    OPENCV2_INCLUDE = fullpath(OPENCV_INCLUDE_ROOT_PATH + "/opencv2");
//    inter_cflags = ilib_include_flag(INCLUDE_ROOT_PATH);
//    inter_ldflags = "";
//    artemis_libs = ["ArtemisHscDefn","Atik.Core","shell32"];
//    //artemis_libs = [];
//
//    inter_cflags = inter_cflags + ' -I ""C:\Program Files (x86)\Windows Kits\8.1\Include\um""';
//    inter_cflags = inter_cflags + ' -I ""C:\Program Files (x86)\Windows Kits\8.1\Include\shared""';
//    inter_cflags = inter_cflags + ' -I ""C:\Program Files (x86)\Windows Kits\8.1\Include\winrt""';
    
    tbx_build_gateway('gw_mqtt', ..
    gw_tables, ..
    gw_cpp_files, ..
    gw_cpp_path, ..
    mqtt_libs, ..
    inter_ldflags, ..
    inter_cflags);

    
endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
