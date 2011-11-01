#define BOOST_TEST_MODULE ConfigParser

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>

#include <configparser.hh>

BOOST_AUTO_TEST_CASE (test_parse)
{
  ConfigParser parser;
  ConfigParser::t_MapConfig keys;

  BOOST_CHECK_EQUAL (parser.parse (std::string (TEST_DIR) + "/ConfigParserTest.txt", keys), true);
  BOOST_CHECK_EQUAL(keys["foo"], "bar");
  BOOST_CHECK_EQUAL(keys["file"], "toto");
  BOOST_CHECK_EQUAL(keys["state"], "bar");
}


