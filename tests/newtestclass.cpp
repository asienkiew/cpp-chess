/*
 * File:   newtestclass.cpp
 * Author: sienio
 *
 * Created on 2013-12-25, 15:10:54
 */

#include "newtestclass.h"
#include "checkboard.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testCheckboard() {
    checkboard _checkboard();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

