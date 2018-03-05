#pragma once

const int CHIN = 17;   // 17 * (a, b) - number of variables for a facial feature is 34 (17 * 2 variables) - reason: it's stored in a 1D array
const int LEFT_EYEBROW = 5;   //  5 * (a, b)
const int RIGHT_EYEBROW = 5;   //  5 * (a, b)
const int NOSE_BRIDGE = 4;   //  4 * (a, b)
const int NOSE_TIP = 5;   //  5 * (a, b)
const int LEFT_EYE = 6;   //  6 * (a, b)
const int RIGHT_EYE = 6;   //  6 * (a, b)
const int TOP_LIP = 12;   // 12 * (a, b)
const int BOTTOM_LIP = 12;   // 12 * (a, b)
const int LIP_DIST = 12;
const int EYE_EYEBROW_DIST = 5;
const int NOSE_DIST = 4;
const int STEP = 2 * (CHIN + LEFT_EYEBROW + RIGHT_EYEBROW + NOSE_BRIDGE + NOSE_TIP + LEFT_EYE + RIGHT_EYE + TOP_LIP + BOTTOM_LIP);
