cc_library(
    name = "opencv",
    hdrs = glob([
        "include/opencv4/opencv2/**/*.hpp",
        "include/opencv4/opencv2/**/*.h",
    ]),
    includes = ["include/opencv4"],
    linkopts = [
        "-lopencv_core",
        "-lopencv_highgui",
        "-lopencv_imgproc",
    ],
    visibility = ["//visibility:public"],
)
