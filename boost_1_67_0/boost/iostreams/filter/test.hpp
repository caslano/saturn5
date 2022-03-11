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
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
*/