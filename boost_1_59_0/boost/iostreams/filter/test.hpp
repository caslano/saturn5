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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) || \
    BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
    /**/
# include <cstdlib>                       // rand.
#endif
#include <cstring>                        // memcpy, strlen.
#include <iterator>
#include <string>
#include <vector>
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) && \
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
    #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) || \
        BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
        /**/
        using ::rand; 
    #endif
}
#endif

namespace boost { namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_string, std::basic_string, 3)

const std::streamsize default_increment = 5;

#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) && \
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
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
*/