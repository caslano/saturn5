// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTER_TEST_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>               // BOOST_MSVC,put size_t in std.
#include <boost/detail/workaround.hpp>
#include <algorithm>                      // min.
#include <cstddef>                        // size_t.
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) || \
    BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
    /**/
# include <cstdlib>                       // rand.
#endif
#include <cstring>                        // memcpy, strlen.
#include <iterator>
#include <string>
#include <vector>
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
    /**/
# include <boost/random/linear_congruential.hpp>
# include <boost/random/uniform_smallint.hpp>
#endif
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>

#undef memcpy
#undef rand
#undef strlen

#if defined(BOOST_NO_STDC_NAMESPACE) && !defined(__LIBCOMO__)
namespace std { 
    using ::memcpy; 
    using ::strlen; 
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) || \
        BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
        /**/
        using ::rand; 
    #endif
}
#endif

namespace boost { namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_string, std::basic_string, 3)

const std::streamsize default_increment = 5;

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
    /**/
    std::streamsize rand(std::streamsize inc)
    {
        static rand48                random_gen;
        static uniform_smallint<int> random_dist(0, static_cast<int>(inc));
        return random_dist(random_gen);
    }
#else
    std::streamsize rand(std::streamsize inc) 
    { 
        return (std::rand() * inc + 1) / RAND_MAX; 
    }
#endif

class non_blocking_source {
public:
    typedef char char_type;
    struct category
        : source_tag,
          peekable_tag
        { };
    explicit non_blocking_source( const std::string& data, 
                                  std::streamsize inc = default_increment ) 
        : data_(data), inc_(inc), pos_(0)
        { }
    std::streamsize read(char* s, std::streamsize n)
    {
        using namespace std;
        if (pos_ == static_cast<streamsize>(data_.size()))
            return -1;
        streamsize avail = 
            (std::min) (n, static_cast<streamsize>(data_.size() - pos_));
        streamsize amt = (std::min) (rand(inc_), avail);
        if (amt)
            memcpy(s, data_.c_str() + pos_, static_cast<size_t>(amt));
        pos_ += amt;
        return amt;
    }

    bool putback(char c)
    {
        if (pos_ > 0) {
            data_[static_cast<std::string::size_type>(--pos_)] = c;
            return true;
        }
        return false;
    }
private:
    std::string      data_;
    std::streamsize  inc_, pos_;
};

class non_blocking_sink : public sink {
public:
    non_blocking_sink( std::string& dest,
                       std::streamsize inc = default_increment ) 
        : dest_(dest), inc_(inc) 
        { }
    std::streamsize write(const char* s, std::streamsize n)
    {
        std::streamsize amt = (std::min) (rand(inc_), n);
        dest_.insert(dest_.end(), s, s + amt);
        return amt;
    }
private:
    non_blocking_sink& operator=(const non_blocking_sink&);
    std::string&     dest_;
    std::streamsize  inc_;
};
                
//--------------Definition of test_input_filter-------------------------------//

template<typename Filter>
bool test_input_filter( Filter filter, 
                        const std::string& input, 
                        const std::string& output, 
                        mpl::true_ )
{
    for ( int inc = default_increment; 
          inc < default_increment * 40; 
          inc += default_increment )
    {
        non_blocking_source  src(input, inc);
        std::string          dest;
        iostreams::copy(compose(filter, src), iostreams::back_inserter(dest));
        if (dest != output)
            return false;
    }
    return true;
}

template<typename Filter, typename Source1, typename Source2>
bool test_input_filter( Filter filter, 
                        const Source1& input, 
                        const Source2& output, 
                        mpl::false_ )
{
    std::string in;
    std::string out;
    iostreams::copy(input, iostreams::back_inserter(in));
    iostreams::copy(output, iostreams::back_inserter(out));
    return test_input_filter(filter, in, out);
}

template<typename Filter, typename Source1, typename Source2>
bool test_input_filter( Filter filter, 
                        const Source1& input, 
                        const Source2& output )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_input_filter( filter, input, output,    
                              is_string<Source1>() );
}

//--------------Definition of test_output_filter------------------------------//

template<typename Filter>
bool test_output_filter( Filter filter, 
                         const std::string& input, 
                         const std::string& output, 
                         mpl::true_ )
{
    for ( int inc = default_increment; 
          inc < default_increment * 40; 
          inc += default_increment )
    {
        array_source  src(input.data(), input.data() + input.size());
        std::string   dest;
        iostreams::copy(src, compose(filter, non_blocking_sink(dest, inc)));
        if (dest != output )
            return false;
    }
    return true;
}

template<typename Filter, typename Source1, typename Source2>
bool test_output_filter( Filter filter, 
                         const Source1& input, 
                         const Source2& output, 
                         mpl::false_ )
{
    std::string in;
    std::string out;
    iostreams::copy(input, iostreams::back_inserter(in));
    iostreams::copy(output, iostreams::back_inserter(out));
    return test_output_filter(filter, in, out);
}

template<typename Filter, typename Source1, typename Source2>
bool test_output_filter( Filter filter, 
                         const Source1& input, 
                         const Source2& output )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_output_filter( filter, input, output,    
                               is_string<Source1>() );
}

//--------------Definition of test_filter_pair--------------------------------//

template<typename OutputFilter, typename InputFilter>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const std::string& data, 
                       mpl::true_ )
{
    for ( int inc = default_increment; 
          inc <= default_increment * 40; 
          inc += default_increment )
    {
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(src, compose(out, non_blocking_sink(temp, inc)));
            iostreams::copy( 
                compose(in, non_blocking_source(temp, inc)),
                iostreams::back_inserter(dest)
            );
            if (dest != data)
                return false;
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(src, compose(out, non_blocking_sink(temp, inc)));
            // truncate the file, this should not loop, it may throw
            // std::ios_base::failure, which we swallow.
            try {
                temp.resize(temp.size() / 2);
                iostreams::copy( 
                    compose(in, non_blocking_source(temp, inc)),
                    iostreams::back_inserter(dest)
                );
            } catch(std::ios_base::failure&) {}
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(compose(out, src), non_blocking_sink(temp, inc));
            iostreams::copy( 
                non_blocking_source(temp, inc),
                compose(in, iostreams::back_inserter(dest))
            );
            if (dest != data)
                return false;
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(compose(out, src), non_blocking_sink(temp, inc));
            // truncate the file, this should not loop, it may throw
            // std::ios_base::failure, which we swallow.
            try {
                temp.resize(temp.size() / 2);
                iostreams::copy( 
                    non_blocking_source(temp, inc),
                    compose(in, iostreams::back_inserter(dest))
                );
            } catch(std::ios_base::failure&) {}
        }
    }
    return true;
}

template<typename OutputFilter, typename InputFilter, typename Source>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const Source& data, 
                       mpl::false_ )
{
    std::string str;
    iostreams::copy(data, iostreams::back_inserter(str));
    return test_filter_pair(out, in, str);
}

template<typename OutputFilter, typename InputFilter, typename Source>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const Source& data )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_filter_pair(out, in, data, is_string<Source>());
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FILTER_TEST_HPP_INCLUDED

/* test.hpp
N12ul7EOeT0SGdGRxtwX4rEhnycO+T5o8V1YMVsv37Xqu5DLp5mDWth74bUhozcOGTda9NNxc/QyblLfhVxG3Rwy5r4Gvw0Z/XHIeG6yNRnT5+plvF59H3IZdXPAmHsGAjZkDMQh4ymLdjwjkbFBfSdyGbVzOAvf423IGIxDRqdFGYPz9DJuVt+LXEbdHCzmt+6QDRlDcch4d4w+px844DCOYSuPoWoUk9Z+jNb5LJbv7iun10z546PX7tyZPDH7vctesh8rWB5r1ziWrzy2rVGMX/sxbOUxk41i/BrHOv7KNDU9O+jcs+WyFxf/9fHZjxVsvwJB/CjuGv2+DPJTnD8x7lqXEJ+tgejSJHQ3CXReosuOUZ7fpN4xAt3hfuN6SwS6gKReWXlBk3o3CnQuE3k3CHQhSb3S8s4a19st0LnPGtd7m0BXQXTZMcprMKl3vKg/Ez1fJtB1S+qVlddrUu8MMY6gSb3TRD+Q1Cstz6TeOQKd8jfjei8X7UZ02eblYY+8cb2LRb2YyFsu0Hkk9crK85rU2yHyZ+LP28V2KalXVl7ApN4asX2YyLtKbJeSeqXlmdRbLdptwLjeZZwOQHTZMcqrGDCud51YnomerxLbpaReWXndJvW+T/QrE3nfK9pNUq+svKBJvQUinYl980S7aeuVl4c9fMb1tojt10TPTaLfU3nZMcrzEF1xjPeW14RujNiOTOg2ivYwoesW9WxCN17Us5ZO3k9iHwLRxerXJHSyfshjQtch6k9CJ2vnfgmdrF0GJHSydhSU0Mn8PiShk/rpOWO6FlF/RFcYw688JnRjRP1J6GR+5Teh6xb1J6GT+VVQQifzq5CWTu5XWMsiuhh+5Tah6xD1J6GT+ZVXQifzK7+ETuZXAQmdtD81oSsQ9cfppH7F4hofGpamnAIo6WnKOMBKQBvADzgIOAE4DyjNwDNAG8APCGSk2Y53fP57+pjH3W9HnmCqJuaxPN7xSYAkzrFZjGMhrvHFiWksxjPWxjIW4xiLMYyLrhLjFstjFu8FaGIVS+IUy2MUa+MT1wHEuMQl31djEtuLRyzEIjaNQxzEvRB/mMceTqFYw0W1yKOWjXLFOMPl3x96nGFZjGEPyvMC5HGGdfGFKbawLK6wJqbwEOMJI45wzPjB+3Qxg+OPFxwrVnAAIMQGlsUFFmMCIx4w6DPQBwBKMtOUCkADoBvQCzgCOA1wZqUp0wArAdsAewAPAI4BTgPSnWnKJMBKwDbAHsCDgOOAECB/eJoyG1AL8AH2Ag4CTgIGAEXZaUo5oAGwG/AA4DggBMgfgbyAOsAuQC/gCOA0IN0FvgA1gDZAD+BBQBAQArhy0hQ3oBbQBdgPOAx4CZCSC54BKwHbAHsADwCOA84AnHkoG+AB+AD7AIkrcSWuxJW4/rXXvzr+3+YbWpp8nSqu79rRsmUG/ogr/p/6W73mqdhneLN63gzO465v9HoVhae3RdK7wg+Kkb4V6e6r8Ns+Nb2jtbm+c0f495l41opnk9YNfsY4pVhy5cUK/0bdTHHafki6Owp4UY3fFGLfjNZUrqpvbG6uR0Hh895z+XmUSGpHmvz8SsrvEOibIRfoZd+OpPTeG1tuRgb5Hj5Onw36GyAvLI5zOaPnTm9mz33KUvxfiPP+xzmwdwtDm0XFyD+syZkO6fm5oHTmfy7R1YFusUo3fCqnWQF6kWYXp8kwpOkFzRKVJrv7kQjNQ7mDaY5EaLK6v2hEczrC94juvVqes3GPx8oncL/fFfu8cjqrmc74JBtSejpPJ1tRupOnk00055/2UCUlVNElgNvV/Sqvch/a3NnSuANRGFGhErEZnqE4qf9QXrLvjYx2M1qi3Hc=
*/