/*
 * File:   queen_test.h
 * Author: sienio
 *
 * Created on 2014-01-04, 17:35:35
 */

#ifndef QUEEN_TEST_H
#define	QUEEN_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class queen_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(queen_test);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    queen_test();
    virtual ~queen_test();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* QUEEN_TEST_H */

