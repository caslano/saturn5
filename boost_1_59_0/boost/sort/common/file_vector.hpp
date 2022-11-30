//----------------------------------------------------------------------------
/// @file file_vector.hpp
/// @brief This file contains functions for to work with random data and files
///        Have functions for to create a vector with random data, and
///        functions for lo load a vector of numbers or strings from the file
///
/// @author Copyright (c) 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_FILE_VECTOR_HPP
#define __BOOST_SORT_COMMON_FILE_VECTOR_HPP

#include <ios>
#include <cstdio>
#include <cstdlib>
#include <ciso646>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <cstdint>

namespace boost
{
namespace sort
{
namespace common
{
//
//-----------------------------------------------------------------------------
//  function : generate_file
/// @brief Generate a binary file filed with random numbers of 64 bits
/// @param [in] filename : name of the file
/// @param [in] NElem : number of 64 bits numbers to insert in the file
/// @exception
/// @return
/// @remarks
//-----------------------------------------------------------------------------
static int generate_file(const std::string & filename, size_t NElem)
{   //------------------------------- begin ----------------------------------
    std::ofstream ofile;
    ofile.open(filename, std::ios_base::out | std::ios_base::binary |
                         std::ios_base::trunc);
    if (ofile.bad())
    {
        throw std::ios_base::failure("could not open file \n");
    };
    std::mt19937_64 my_rand(0);

    for (size_t i = 0; i < NElem; ++i)
    {
        uint64_t Aux = my_rand();
        ofile.write((char *) &Aux, 8);
    }
    ofile.close();
    return 0;
};
//
//-----------------------------------------------------------------------------
//  function : fill_vector_uint64
/// @brief : fill a vector of uint64_t elements from a file
/// @param [in] filename : name of the file
/// @param [in] V : vector to fill
/// @param [in] NElem : number of elements for to read from the file
/// @exception
/// @return
/// @remarks
//-----------------------------------------------------------------------------
static int fill_vector_uint64(const std::string & filename,
                              std::vector<uint64_t> & V, size_t NElem)
{   //----------------------- begin ------------------------------------------
    std::ifstream input(filename, std::ios_base::in | std::ios_base::binary);
    if (input.fail())
    {
        throw std::ios_base::failure("could not open file \n");
    };
    //------------------------------------------------------------------------
    // Calculate the lenght of the file and the number of elements inside
    //------------------------------------------------------------------------
    input.seekg(0, std::ios_base::end);
    size_t length = input.tellg();
    size_t uCount = length / 8;
    if (uCount < NElem)
    {
        throw std::ios_base::failure("incorrect lenght of the file\n");
    };
    V.clear();
    V.reserve(NElem);

    uint64_t Aux = 0;
    input.seekg(0, std::ios_base::beg);
    for (size_t i = 0; i < NElem; ++i)
    {
        input.read(reinterpret_cast<char *>(&Aux), 8);
        V.push_back(Aux);
    };
    input.close();
    return 0;
};

//
//-----------------------------------------------------------------------------
//  function :write_file_uint64
/// @brief Write a file with the contnt of a vector of Uint64_t elements
/// @param [in] V : vector from read the numbersl
/// @param [in] filename : name of the file
/// @exception
/// @return
/// @remarks
//-----------------------------------------------------------------------------
static int write_file_uint64 (const std::vector<uint64_t> & V,
                              const std::string & filename)
{   //--------------------------------- begin --------------------------------
    std::ofstream ofile;
    ofile.open(filename,
                    std::ios_base::out | std::ios_base::binary
                                    | std::ios_base::trunc);
    if (ofile.bad())
    {
        throw std::ios_base::failure("could not open file \n");
    };
    for (size_t i = 0; i < V.size(); ++i)
    {
        ofile.write((char *) &(V[i]), 8);
    }
    ofile.close();
    return 0;
};
//
//-----------------------------------------------------------------------------
//  function : fill_vector_string
/// @brief fill a vector of strings from a file
/// @param [in] filename : name of the file from read the strings
/// @param [in] V : vector where store the strings
/// @param [in] NElem : Number of strings for to read from the file
/// @exception
/// @return
/// @remarks
//-----------------------------------------------------------------------------
static int fill_vector_string (const std::string & filename,
                               std::vector<std::string> & V, size_t NElem)
{   //----------------------- begin ------------------------------------------
    std::ifstream input(filename, std::ios_base::in | std::ios_base::binary);
    if (input.fail())
    {
        throw std::ios_base::failure("could not open file \n");
    };
    //------------------------------------------------------------------------
    // Calculate the lenght of the file and the number of elements inside
    //------------------------------------------------------------------------
    input.seekg(0, std::ios_base::end);
    V.clear();
    V.reserve(NElem);

    std::string inval;
    input.seekg(0, std::ios_base::beg);

    for (size_t i = 0; i < NElem; ++i)
    {
        if (!input.eof())
        {
            input >> inval;
            V.push_back(inval);
            inval.clear();
        }
        else
        {
            throw std::ios_base::failure("Insuficient lenght of the file\n");
        };
    };
    input.close();
    return 0;
};

//
//-----------------------------------------------------------------------------
//  function :write_file_string
/// @brief : write a file with the strings of a vector
/// @param [in] V : vector from read the sttrings
/// @param [in] filename : file where store the strings
/// @exception
/// @return
/// @remarks
//-----------------------------------------------------------------------------
static int write_file_string (const std::vector<std::string> & V,
                             const std::string & filename)
{   //--------------------------------- begin --------------------------------
    std::ofstream ofile;
    ofile.open(filename,
                    std::ios_base::out | std::ios_base::binary
                                    | std::ios_base::trunc);
    if (ofile.bad())
    {
        throw std::ios_base::failure("could not open file \n");
    };
    for (size_t i = 0; i < V.size(); ++i)
    {
        ofile.write((char *) &(V[i][0]), V[i].size());
        ofile.put(0x0);
    }
    ofile.close();
    return 0;
};
//---------------------------------------------------------------------------
/// @struct uint64_file_generator
/// @brief This struct is a number generator from a file, with several options
///        for to limit the numbers between 0 and Max_Val
/// @remarks
//---------------------------------------------------------------------------
struct uint64_file_generator
{   //----------------------------------------------------------------------
    //                  VARIABLES
    //----------------------------------------------------------------------
    std::ifstream input;
    size_t NMax, Pos;
    size_t Max_Val;
    std::string s;

    //----------------------------------------------------------------------
    //                    FUNCTIONS
    //----------------------------------------------------------------------
    uint64_file_generator(const std::string & filename)
    {   //---------------------------- begin ---------------------------------
        s = filename;
        input.open(filename, std::ios_base::in | std::ios_base::binary);
        if (input.fail() or input.bad())
        {
            throw std::ios_base::failure("could not open file \n");
        };
        //--------------------------------------------------------------------
        // Calculate the lenght of the file and the number of elements inside
        //--------------------------------------------------------------------
        input.seekg(0, std::ios_base::end);
        size_t length = input.tellg();
        NMax = length / 8;
        Pos = 0;
        Max_Val = ~((size_t) 0);
        input.seekg(0);
    };

    void set_max_val(size_t MV){ Max_Val = MV; };

    size_t size() const { return NMax; };

    uint64_t get(void)
    {
        uint64_t Aux;
        input.read(reinterpret_cast<char *>(&Aux), 8);
        return (Aux % Max_Val);
    };

    uint64_t operator ( )(){ return get(); };

    void reset(void) { input.seekg(0, std::ios_base::beg); };

    ~uint64_file_generator() { if (input.is_open()) input.close(); };
};
//
//****************************************************************************
};// end namespace benchmark
};// end namespace sort
};// end namespace boost
//****************************************************************************
//
#endif

/* file_vector.hpp
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
*/