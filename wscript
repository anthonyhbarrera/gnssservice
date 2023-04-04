#! /usr/bin/env python

import os, sys, re, shutil, subprocess, traceback, types
from waflib import Configure, Options, TaskGen, Task, Errors, Context, Build, Utils, Logs, Scripting
from waflib.Ficosa import Ut
from waflib.Ficosa import gtest, gmock
Test = Ut.UtContextBase.execute_ut

top, out, Configure.autoconfig = '.', 'build', True

VERSION = '1.0'

def options(opt):
    opt.add_option('--list', action='store_true', default=False, help='List UTs.')
    opt.add_option('--compiler', action='store_true', default=False, help='Compiler to load.')
    opt.add_option('--target', default=True, help='Target config to use.')
    opt.add_option('--variant', default=True, help='Target variant to use.')
    opt.add_option('--all', action='store_true', default=False, help='Test to execute.')
    opt.load('g++')
    opt.load('testcocoon')
    opt.load('xsltproc')
    opt.load('gtest')
    opt.load('gmock')

def configure(conf):
    conf.load('gcc')
    conf.load('g++')
    conf.load('testcocoon')
    conf.load('xsltproc') 
    conf.env.GTEST_SRC = '5_Tools/gtest_gmock'
    conf.env.GMOCK_SRC = '5_Tools/gtest_gmock'
    conf.env.UT_REPORT_TEMPLATE = '5_Tools/ut_templates/execution_report.html.template'
    conf.env.UT_REPORT_FILES = '5_Tools/ut_templates/img'
    conf.env.UT_TESTPLAN_TEMPLATE = '5_Tools/ut_templates/testplan_report.html.template'
    conf.env.UT_TESTPLAN_FILES = '5_Tools/ut_templates/img'
    conf.load('gtest')
    conf.load('gmock')

def build(bld):
    pass

def ut(utctx):
    #Recursively load all the component tests.
    v = utctx.env
    utctx.add_test(
        name        = 'Test_GnssDbus',
        source_test = [
            '4_Test/Unit_Test/Test_gnssDBus.cpp',
        ],

        source_uut  = [
            '3_Implementation/gnssDBus.cpp',  
        ],

        features    = 'c cxx googletest googlemock testcocoon',

        includes    = [
            '4_Test/Unit_Test/Gtest_Main',
            '4_Test/Unit_Test/Test_GnssService', 
            '4_Test/Unit_Test/Test_GnssService/templates', 
            '4_Test/Unit_Test/Mocks',
            '3_Implementation',
        ],

        defines     = [
            'UNIT_TEST',
            'COVERAGE_ENABLED', 
            'COVERAGE_MCDC',
        ],

        cflags      = '-ggdb',
        cxxflags    = '-ggdb -std=c++17',
        linkflags   = '-ggdb',

        tcflags    = '--cs-exclude-file-wildcard=*Test*',
    )
    utctx.add_test(
        name        = 'Test_GnssParseNmea',
        source_test = [
            '4_Test/Unit_Test/Test_GnssParseNmea.cpp',
        ],

        source_uut  = [ 
            '3_Implementation/gnssParseNmea.cpp',
        ],

        features    = 'c cxx googletest googlemock testcocoon',

        includes    = [
            '4_Test/Unit_Test/Gtest_Main',
            '4_Test/Unit_Test/Test_GnssService', 
            '4_Test/Unit_Test/Test_GnssService/templates', 
            '4_Test/Unit_Test/Mocks',
            '4_Test/Unit_Test/Stubs', 
            '3_Implementation', 
        ],

        defines     = [
            'UNIT_TEST',
            'COVERAGE_ENABLED', 
            'COVERAGE_MCDC',
        ],

        cflags      = '-ggdb',
        cxxflags    = '-ggdb -std=c++17',
        linkflags   = '-ggdb',

        tcflags    = '--cs-exclude-file-wildcard=*Test*',
    )
    utctx.add_test(
        name        = 'Test_GnssService',
        source_test = [
            '4_Test/Unit_Test/Test_GnssService.cpp',
        ],

        source_uut  = [ 
            '3_Implementation/gnssService.cpp',   
        ],

        features    = 'c cxx googletest googlemock testcocoon',

        includes    = [
            '4_Test/Unit_Test/Gtest_Main',
            '4_Test/Unit_Test/Test_GnssService', 
            '4_Test/Unit_Test/Test_GnssService/templates', 
            '4_Test/Unit_Test/Mocks',
            '3_Implementation', 
        ],

        defines     = [
            'UNIT_TEST',
            'COVERAGE_ENABLED', 
            'COVERAGE_MCDC',
        ],

        cflags      = '-ggdb',
        cxxflags    = '-ggdb -std=c++17',
        linkflags   = '-ggdb',

        tcflags    = '--cs-exclude-file-wildcard=*Test*',
    )
    utctx.add_test(
        name        = 'Test_GnssUdp',
        source_test = [
            '4_Test/Unit_Test/Test_GnssUdp.cpp',
        ],

        source_uut  = [ 
            '3_Implementation/GnssUdp.cpp', 
        ],

        features    = 'c cxx googletest googlemock testcocoon',

        includes    = [
            '4_Test/Unit_Test/Gtest_Main',
            '4_Test/Unit_Test/Mocks',
            '4_Test/Unit_Test/Test_GnssService/templates', 
            '3_Implementation',
        ],

        defines     = [
            'UNIT_TEST',
            'COVERAGE_ENABLED', 
            'COVERAGE_MCDC',
        ],

        cflags      = '-ggdb',
        cxxflags    = '-ggdb -std=c++17',
        linkflags   = '-ggdb',

        tcflags    = '--cs-exclude-file-wildcard=*Test*',
    )
    utctx.add_test(
        name        = 'Test_GnssMain',
        source_test = [
            '4_Test/Unit_Test/Test_GnssMain.cpp',
        ],

        source_uut  = [ 
            '3_Implementation/main.cpp',
        ],

        features    = 'c cxx googletest googlemock testcocoon',

        includes    = [
            '4_Test/Unit_Test/Gtest_Main',
            '4_Test/Unit_Test/Test_GnssService', 
            '4_Test/Unit_Test/Test_GnssService/templates', 
            '4_Test/Unit_Test/Mocks',
            '4_Test/Unit_Test/Stubs', 
            '3_Implementation', 
        ],

        defines     = [
            'UNIT_TEST',
            'COVERAGE_ENABLED', 
            'COVERAGE_MCDC',
        ],

        cflags      = '-ggdb',
        cxxflags    = '-ggdb -std=c++17',
        linkflags   = '-ggdb',

        tcflags    = '--cs-exclude-file-wildcard=*Test*',
    )

    #Implement options.
    if utctx.options.list:
        utctx.list()
    if utctx.options.all:
        utctx.execute_all()
