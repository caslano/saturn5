//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593
#define BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_name_,std::string> errinfo_file_name;
    }

#endif

/* errinfo_file_name.hpp
q0MtI0h8U4oAMZ3Mhu9nn7qfhuPLbZ1hQdG4wBwao9mtmZJLqI5MVNDquNulTj8e4p3p7ZgetMLUQnoj7PR/imcz/3A390l+tiX+B1BLAwQKAAAACAAtZ0pSD14xZPIEAAAUCwAAMQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUFJPWFlBVVRILjNVVAUAAbZIJGCtVW1v2zYQ/q5fcfA+zA5U2VkHpG8rpjjuotW1BEtuasCAQEtUxEUWNZJKYqz77zuSUlw3HZoPVeBIou6eO949z9HbDODkh12Op+Hgu1dqfileeO+dIsH/opn6tkOafgb7h44bvD8h1BgOXp/TETzJ6zMMjVfaxXqjn9P0CeE2Okn9b6ydN6l+xBXr2flPebMX7LpUMJyO4PTlyxfwDH6ZnJ65cEFqRiuIFa23VFy78CY3K7+X5P7ek/StC1QBqbwjwKRkEiQv1B0RFPC5YhmtJc2BSMipzATb4gurQZUUClZRmIbROlj84cJdybKyw9nzFmTJ2yqHktxSEDSj7NbCNEQo4AUiIH7OpELMVjFeexiegqJiJzsYnQSpJAdyS1hFthiOKCiVauSr8ThrRYU7Gec8k+OsL4VXqt1Xu1pjNjuyB94oUBxa
*/