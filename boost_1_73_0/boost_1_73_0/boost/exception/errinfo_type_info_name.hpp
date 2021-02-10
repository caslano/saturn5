//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593
#define BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //BOOST_THROW_EXCEPTION(
    //    bad_type() <<
    //    errinfo_type_info_name(typeid(x).name()) );
    typedef error_info<struct errinfo_type_info_name_,std::string> errinfo_type_info_name;
    }

#endif

/* errinfo_type_info_name.hpp
L2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BST1hZSEVBREVSLjNVVAUAAbZIJGCtVVFv2zYQftevOHgPtQNHTpYBabK0mOq4jRdXMiy5qQEDAi1REVda1EQqjrfsv+9ISnGSpkgeKsOmTPK++3h339FddmDvpz2Oq+HgxSc23xgfHFujaSX+ool63iCO78B+0HCJ4ytcDWBndRf34FVWd9A1VnHj60y/x/Er3C01Sf0z0MbLWL/ijLVs7Iei3FbsOlfQHfbg8OTkLezDrweHx304JwWjHEJFixWtrvtwlpqZP3Jye+tK+r4PVAHh7iPAKGcSpMjUhlQU8J2zhBaSpkAkpFQmFVvhH1aAyilkjFMYBtPF2P/Uh03OkrzB2YoaZC5qnkJObihUNKHsxsKUpFIgMkRA/JRJhZi1YqJw0T0FRau1bGA0CcKlAHJDGCcrdEcU5EqV8nQwSOqK40kGqUjkIGlD4eZq/eRUC2SzJlsQpQIloJa0D3p/H9YiZZkeMUQ4WdYrzmTe39FCh0U6EBVIynkDh6aMSnsECmETrb7eCSWyZ0oPUhRSe9vkYv1oI4a1AcrqqkB3GBbclwoMfB/qIqWV2W8C0XppomxC/kLKdtxTEAWygo4XwjjswIpIJvtwNY4ugnkEV95s5vnR
*/