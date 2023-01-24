// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_


namespace boost
{
namespace process
{
namespace detail
{
namespace posix
{

template<class StringType, class Executor>
inline void apply_exe(const StringType & exe, Executor & e)
{
    e.exe = exe.c_str();
}

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* exe.hpp
wgi51RUy+/L+6qy+mFJxHomXL8eodorLYlUg4iunelD8qSvQ+7GDQOj6RkVso3wXfbM9UPK6pHDQhCHi9/3OIq7dV3trbMux1UxOB1YhnS8mkyMLiZyFqtJSPknpIoXZzaJTfzUHWUiuXp87PjR4UaTQVg60+mSVbdO5vSX2bhfMeUSx+1rKxI3JEbzgOTcTS7BIrjwZhgeLNSF9L4Or8lE6c/IufHafttXb2cEBZGRxWcAs0yncM12xDD6IehjXF5lNXCY+Pz1/cH/q7L7ozpXaGG+6sJhhZFDDR1U8JTfUvLCb9uUuIk2//fa6U4Cou1zJhMaT5wk5j3rsOwJ23X2u507c8mOVcfIFvQpAbJwXRsJDPgkMrF6KITkCdV2+8e9ckwOVqvvU+o/rSUSek2YbwdaJ8p8OqE3ZOB50MC/wvhmIRmjaqXKoG+8Vvrm/U1FO4AHke9DyUM7Tn4vrEjlODlTptIj6uXOhp8lW2GLcr6jpMk6rGeREDCb1idjr5tiSGZXyt3fxZw0mPYnktvC32pWl7W4cDCUJeXr/VS/BFN5Q7CpFommaAcqjiPsonfCtKMmKJ1ycnvfg4RwSS929z/57TH6Ccb5j4nnzogffW05k+wKDsb7Eu6DxWE5HdaB3x5XVwFRQkhizYoLDbPV7lZGYs5MYt0x7+bFnKcysHG4/B4Zoif/9QQxYXpH/otvyut4oARypBMvD
*/