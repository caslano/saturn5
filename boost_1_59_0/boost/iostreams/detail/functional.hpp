/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/functional.hpp
 * Date:        Sun Dec 09 05:38:03 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com

 * Defines several function objects and object generators for use with 
 * execute_all()
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/close.hpp>
#include <boost/iostreams/detail/ios.hpp> // BOOST_IOS

namespace boost { namespace iostreams { namespace detail {

    // Function objects and object generators for invoking
    // boost::iostreams::close

template<typename T>
class device_close_operation {
public:
    typedef void result_type;
    device_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }
    void operator()() const { boost::iostreams::close(t_, which_); }
private:
    BOOST_DELETED_FUNCTION(device_close_operation& operator=(const device_close_operation&));
    T&                   t_;
    BOOST_IOS::openmode  which_;
};

template<typename T, typename Sink>
class filter_close_operation {
public:
    typedef void result_type;
    filter_close_operation(T& t, Sink& snk, BOOST_IOS::openmode which)
        : t_(t), snk_(snk), which_(which)
        { }
    void operator()() const { boost::iostreams::close(t_, snk_, which_); }
private:
    BOOST_DELETED_FUNCTION(filter_close_operation& operator=(const filter_close_operation&));
    T&                   t_;
    Sink&                snk_;
    BOOST_IOS::openmode  which_;
};

template<typename T>
device_close_operation<T> 
call_close(T& t, BOOST_IOS::openmode which) 
{ return device_close_operation<T>(t, which); }

template<typename T, typename Sink>
filter_close_operation<T, Sink> 
call_close(T& t, Sink& snk, BOOST_IOS::openmode which) 
{ return filter_close_operation<T, Sink>(t, snk, which); }

    // Function objects and object generators for invoking
    // boost::iostreams::detail::close_all

template<typename T>
class device_close_all_operation {
public:
    typedef void result_type;
    device_close_all_operation(T& t) : t_(t) { }
    void operator()() const { detail::close_all(t_); }
private:
    BOOST_DELETED_FUNCTION(device_close_all_operation& operator=(const device_close_all_operation&));
    T& t_;
};

template<typename T, typename Sink>
class filter_close_all_operation {
public:
    typedef void result_type;
    filter_close_all_operation(T& t, Sink& snk) : t_(t), snk_(snk) { }
    void operator()() const { detail::close_all(t_, snk_); }
private:
    BOOST_DELETED_FUNCTION(filter_close_all_operation& operator=(const filter_close_all_operation&));
    T&     t_;
    Sink&  snk_;
};

template<typename T>
device_close_all_operation<T> call_close_all(T& t) 
{ return device_close_all_operation<T>(t); }

template<typename T, typename Sink>
filter_close_all_operation<T, Sink> 
call_close_all(T& t, Sink& snk) 
{ return filter_close_all_operation<T, Sink>(t, snk); }

    // Function object and object generator for invoking a
    // member function void close(std::ios_base::openmode)

template<typename T>
class member_close_operation {
public:
    typedef void result_type;
    member_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }
    void operator()() const { t_.close(which_); }
private:
    BOOST_DELETED_FUNCTION(member_close_operation& operator=(const member_close_operation&));
    T&                   t_;
    BOOST_IOS::openmode  which_;
};

template<typename T>
member_close_operation<T> call_member_close(T& t, BOOST_IOS::openmode which) 
{ return member_close_operation<T>(t, which); }

    // Function object and object generator for invoking a
    // member function void reset()

template<typename T>
class reset_operation {
public:
    reset_operation(T& t) : t_(t) { }
    void operator()() const { t_.reset(); }
private:
    BOOST_DELETED_FUNCTION(reset_operation& operator=(const reset_operation&));
    T& t_;
};

template<typename T>
reset_operation<T> call_reset(T& t) { return reset_operation<T>(t); }

    // Function object and object generator for clearing a flag

template<typename T>
class clear_flags_operation {
public:
    typedef void result_type;
    clear_flags_operation(T& t) : t_(t) { }
    void operator()() const { t_ = 0; }
private:
    BOOST_DELETED_FUNCTION(clear_flags_operation& operator=(const clear_flags_operation&));
    T& t_;
};

template<typename T>
clear_flags_operation<T> clear_flags(T& t) 
{ return clear_flags_operation<T>(t); }

    // Function object and generator for flushing a buffer

// Function object for use with execute_all()
template<typename Buffer, typename Device>
class flush_buffer_operation {
public:
    typedef void result_type;
    flush_buffer_operation(Buffer& buf, Device& dev, bool flush)
        : buf_(buf), dev_(dev), flush_(flush)
        { }
    void operator()() const
    {
        if (flush_) 
            buf_.flush(dev_);
    }
private:
    BOOST_DELETED_FUNCTION(flush_buffer_operation& operator=(const flush_buffer_operation&));
    Buffer&  buf_;
    Device&  dev_;
    bool     flush_;
};

template<typename Buffer, typename Device>
flush_buffer_operation<Buffer, Device> 
flush_buffer(Buffer& buf, Device& dev, bool flush)
{ return flush_buffer_operation<Buffer, Device>(buf, dev, flush); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED

/* functional.hpp
ZGXSQWo9ftEq6EwScJ1FI6LDVbufisDxpkkyov3ZEtmWinG5zqdBo2yBvQdCEFAJqRaNHzF2iL+J8i0NJcWvE1T6uKJls1bczWDEtjQXYB8YK34BxysJjYCbUCg5POIhFPAd6rJK2MhEkGjuyTpYDVNkoHZ0OMWxjG9y+Y+uxODPwcD0/nLz6veoR6gQx49+UcuNemEXW3Ni7hMZZ1o5FyczX6lD22E0Ne57UJOU7RcLfUBh5njeGjTtX6lkex2RfkFKnDEnNqhxbUnE0qWgg6+4R3gyd+yP1o95F4cTjQxL4Ylp9d2STr5Ay5eh0VNdZZkSWtT+CWC1LBJAHehf/4kjaAF/v1y9fKkQKH8S+8c4vKST81jAy9fjcuk/fQ19k3MGamsw9KVsQfPz9oPyWnngpPZSU/SWmCdxxOK0Adl8Q9LyuslT9r+7NrtJcF9LIKlpPeExV4tT0mpXhw7Hl+CWi5KvGbnmNNVB6Ps66iBqxC7Q+eKS8GAWIR/VMyGWObh9+kNeoPLv9ANDG/u1Wmro+Qy5VjQime/QrwZoAqJUZLmAKIoxQnZQiPoUldeyONkZs5gFS9zr0tzVHLIIqDiYCk5Ryhks0rl+MDk/oBnOBA875DZ3J51APtZ4P1KowEbFvHy2XPbA+GmN4j5bzT8SB8ESaCowzMWM0bixzgSRHAxfnmdVecPqYZcnduEBv3LNtSG/J1pyDfvGSo1lbXZ7gWJT+RJz9VHfobd2PUWuAp5jXQ2rTh7ePfsiGmecd3X/LwdbxnjiKQ9Qa1mZKQbHeJr7Mosh9W5VEAIJYt9cOIJR8bsU4/XVEwEe63BV8nCjvoLxI0gZXS7rxVq3LUJoV9G0rCrH7x7kZCvu39PIfPnF6c8ANeSb1Ib6tLoSLATcA1Iwl+tyuBSEYzoq++ZSTy1ZlY4hDnmk287UAcbJgaCgwyUE/8JsTLr6AWAYsei18+MTCq0+K5ESUX2N1wrEObg5JmfJPG7Vgni8jhosvR/DqrnzXddQyPZcqc5g9TC3tz+yrsocP3tp0QECyBVkqWFG2aREH6l6ajvtpkwUD6I40QqMorvsMwkjZ6a3nBrPoEakN9AK1IshSnaDUVL7UtibsQ7FPSdtc6kpsTvyDjQl5j6u9QOSEJaE2mrG8gAH9UHSVxWTB2sug6wLRpsLHEPsXV2zKBW7JuCTXDZ4vMCxPcDRFq6qBaJEMJhInq+GhkXidQmOLEdZdOVoJP5uJNJkOk22UP7+w8Skp4GV73kLweskkucGNjDYW0P1fI6BRZpKGmjzB6wB3yEZ5X9PtTnMQmQXwyvlCvThUR7BJQCz7/7KkNgwPcNHcV9bqQBM0MDlEkpMmpZpLoh0cfiUsbRYs/6sC/fho9SYsLnivj1kzLZLSTEj0JcckmiT+CdAFVHdGnnWIulIloi+OyaFJeWMqyAyMBhFR+Fu66GpOtFHWB2dxFMyYDTpebIa/YVsSLCFTT3Ggs59aYZy9QRet/xHZQiJIRkZcHCK3tVOA44jidgautZX8g4CBZGkDeSGS6gq/zDKaDY/aao1karFK8o9Ejk2aL29bXy29LVZxG0mqmUSHuy47nzuduTqFXBKGyc1qfDWsLRnnpR9dCwtbdEY42hQVwXWRUnVbXbi6S81vW0oVX92/E8qeUqTu/cQ7AnL1oe+n5JB/uVnD/gqZK19s4tb/fXZ66gPRnjz2JdkXX3Z1s5LDtli1XfdgEjSFmYBNZmRxoFN8FJyQdz23P6sGWC184g0qjelUFxWumPO1lPUnWHaihjt90YT51mJ6w65gkfTUzuNIcFciryFQBSkleh/se7es+XMPU7wUEq1vj39Ez7MmrwW/0JzcpKuqwSuN1HWGiOktgGqCRlc2xNSf6mbobV/b9zv27ixupdSFTmGqkgXYRwn9um2x981LlqHsRf9dFbnqouR5zt8m+xh9cvROP02k4sFifk2cDmDCyA3tQH1kMX/03uYAusxWDjE9r0IQgwxooeYAcy9Syg6vUNfeEvLVieeP+A9ySRbohJJVA35jRjNpU+NXG7elE4Zg+ld6Btk+EqpssWPr5ekw7UNP1BcTMkNBxhDdQK2x7UDkobl7hw5TR9KA/Y9tcYThjgV4iq7ajOib+5YGjOGgq9Nfkn2x7JLo98voCvIxAuloQFcpfYAJIUsJvEd/Ct8wP/uW6BeY77b0VcTzpZfPHvCHegaDoPsUHki0BN3CZ8GGFKtofuVwEJvelHvTkar4xT9oQYqb8JcvJs+2PEcVbQxU+GWLEBJpPSJOMRksoF4BM6tcPNhrQiUi+LW8k6C1dbHNxmlL9nhyiogEj1rmI38KNko4EPae6m822qeq0Fq/sy8kzygKnsLN/MAEyzs020xkeUOVcDckqpVnxEsvVM/Cylux8EfCraUxt8IEfhwR2EIaVPf7Jy+Jaqd7d5sUD5oTHjGg62fnc9D7MnC0GLSS/hXaiTL4NvDwcA55uKASGsMaWpTU1wkfec34eLZ4q1k0YdR3Mo7e/zXpoJXZd0Pm4/ryOGiZCF5HlxrQQ1g6HZa/SfPQO+APoDWJjr83A8nfRXEAEoBKAyOysMH+ijhlMS0yi15Y/Srj8jzA01UGoASFGJVF8+OFQvimeJcfFptxjvJ4yYqX2GUgui8n2XUBu0+p2dpBNHbn9YIZRY9x7/p+XcX8ox3KwwZzmFslUCCzoFpOQ2vF5CKd9REJoaehe/2nm03pSYry+dkbx9yxniOd/UoYaONjwkD63cqyMqEa9i1KnzBEV9U9EXvbJLndk4FK8cpU0V13w5npMqH4n3tBsm4Z+ojfFJzRQqgCTPN0Y4YDpbpZYjtg2dZQr0CWx++HSu6mZBDRk5OtW1lKWLmH9uaFjLh/3V0xXLSv5q3lh4L/c884VujSQ4Z6ihE0tjbr2WsgPBU88E3hZ2grFbvgA2RY58AMYlXACPM/mnFGI+bhWxMocS+HOSiETp+IYrhxw7TV5sPfxEIVPo0809T5+fLio6XIJS5VrLc3nzgtoD4xBXuizUTMKwWHV8vEOXEvcDzdicgi2h6E9Uc4djkoyLhqhbFjB3WmCAyy9A+MXIz+jQeeAWDwTfQHR5jb7qKP0fBHXUol0HljjAyeOGFqcJ+Il8/h+BSxwXP4H0J/b54ie4b5lsMF8xuxIRW9CYLcaexoajOkFsB63pgk6gWCDpYZfTtWuyOIjR4rc/3NEpK4OXLQc6XwqfijyS9WSsnmJTyCcoMOI0kt/pOd6yYVWJuMfJMdf3IW07XP6ze89yZJkojBu7+tOsT87CGIOWlAAsklj/VwoSALv47477cXYEwZz6/dGy7gSCac9uhAYTdWvYKbipXwDp3jAvAuls7leQdgBesOfvukoar7s4QEkSPLOKyVj0oRK0CC1KpVw5iRzwjUC2Ok2ohsk/gg42JWDadVjyVuBKx3NVqyO/BG8k10QczhTOnbPBcHl6z53L3cqPJr8qO+dt0kifJ08YP6wVKK6iAr0Ak4PihEmx04bvCYlTpjrsqC2ZIHtkYoeJRKU4NHF6qu3rx4yHU+c8OirD0gv5tc72iXzJWucWsM1pPI3A6FDb6sUz7iPDClnfcbJzLh62NwXivaie8G5HgGqiVc0hiNWoJyThryg+RlCt/VxpjTM9k6ghz+y5i7ffH7rBk8CPJWx1rHZmMS3ac+q8NLDUX+oe1qLM2F5hAqf8IMjPEvM0Wcc8yjFiND6qFLCVkhNRJkUFEmKsyxVJ/R+UliebBxWlemd2y7F1EIzquisNQUZJLq+ruEMQv5/fHGYyHkemWqhiqrcYNN7mS31C4Dr90cvEltXBewXVm3Neuoqf4vMiJAqCf3jGGM0elq+sfze6tLuVHe04s4bnCbnIj9qNrzWj89u3itw+K5XMeUT0/sBhhPrFK/Qw7D1osWo0q58aH+NWjDgAMLcge/J5U0aWGqK1WQ4+VUgPSQbS3C79juDlbCsEXOqtxJWaEvl9nlkuAmc9AyyCyKmcZK12UC8j8FZwiaujG7vs4daGdq3/dyuBo5XEBKKQZcTA+w+Nk1lmZQv+dR/DyHssmPnbX5Itg9xddabSCqWHgsIkO2aJfm7Y7TxftcYy6RXaL4Dmu8z2FWyJhX1OY9T9UqndACg4saIGnTNOxLjksfU1P2bT6bEeoxuwFHDKJzICcwPS5YjcYPh8mxeRBhHRtUt0GoOq6fzKChEXehIZ70qh7QJXO7KmPt/QwRL6OM+EK4zN2v4KmycJeaexyxRht4+x01KTWfSyAHHXKuEt3TSlIT8txiBCdg4viYvL6AbFLhB76D85zW+PrXF5YgI5wEAsAmlOxlhqTCAmd+377+xMZGHoxP6WPDkZQsHoLz6FPx0mzKCtdR8dt45gYTQIQLbQ4kWdN6MqJF/HoVTr0H+a3g9yzSpH1N0AskoFteE4aUZ9y9UDYIvf12zmPCNEsRBRyhBxjO8wEMW+Vm5zeyKQJIn5HWbR4d6icmcrSNhkcqqv0CakU5Ta7+jtiuFiUB8l6Ot1/fMQ3umjXUZ8LMHZaJJ9EwDfeWtVxAqMJbEwhYe0dgBGoIIsnnF40SsdCqZcNqooKpkH9DIGjitu9v+R9MU6fqaqcIeMn3rUFq6R/Z2kq/KGgAZJY+lAoRF97HIJxpHgXjM+/UTCXHpFl+MEj1Gsb3NXknK5qeS1bTx752/tk0/DUATnjdLrbLHJOzz+Q+cmqLb/mT93Tfo09N1J4DNnRhhpMHYLUbSYL5jXf3/VbGMus0+PlHLfxIac/xGPZ1hoeh5xCetLpY7iKWZPP1Bp+MWWbwtcNf1gypUgEQkWgqdPOYdUwr38YmOD5Mo7k0DuECGGs4YT/0H+q5CNRKOUpG46QjXT59FJ+oRnTrPSygcmOzCaomxQpdygfP3Luezr3stqD+zcIpzN4MONnPQbZhvCtqPUIr3eCwCsgIP7KAxqDd1O2CBU8zUO8bZH0MJu7u5rabOlh6WCAc34lU/gicXl9gHkKk8hiI6/+G+z5igu3oyr2z5yHCzxVCr+cn96kcs5UYuyAGkmzUsY4mxaznpZAcuA2UNWsA6xaMgC0OGc/PjzC4UEHTwWYLTuMHsLFieqMBpa8LeDlw5OO6FvkaQVf06PcwvdS/nW2a4QoIXGJrmJuKjBfg7cjsc2xb9e+23o1YeikktwKLz+YADlq9D+LYJbSmoggkJ60ZrwFK0MkGxtzraCbdSNpvlTPFS2AEs53oWTrO+CPuAmrBeXy24a9dXogZzdBEBKsOUr3wIzPp5GAhrKqv3wkd0IgEnFYEuCBMzjE414v0GNmXP00uEsxMJsO6IvlGXE5FvdGdDuwHkmQlqC42hJmc5jpoz8bhRutBOXxYicWe0cKyxHpKmEAzyejzC5zF7GtMR1ENiix9g54i01pTxJEPdBRs4/MqbolPGddvenc7fqeOlrRHC6LEuHwX4FLkKSmh+KJpGXbij0kqaRI2HsiX11LBhvJAAoOEBSXAu9UZtt9tWN5zVOAeqCYr0lF8GFBIRm0uustLWcYeZSCcyzM67/nRpAHlukwigwFYT8XjUCcd2If2OuaSHsDSz1zyWpL9djesZnbqxL1ynl67ZkTFOUk7Rw14oK2/xwO/oH2TPLWDz3h9gC73llqLelpCP09FOW7VSA/xEAo9wMIRIDLfiOQV7E1oytecAhYvfSsjPLZa+IV3v2m4m4jRWbR5e0nWh6OHw1o9u7p/E08gaNeQ8pEnOXc6Fr3Br2rvCT74fRv9jddAOhIkVb3vTU73w7sbMEN+NzB0kjw1Bgtet7MQZ8IwPHEnAIDbMQoCL8tAu5RB7CTjNe2apQlaRd6R7qCbds+f8CAklEVC0ZRQSCVFX1F8czb5AjXDcygvWxpgVRKrsywNNWxxKDbO1F3/DC3l+2pZxLD380aa4RTNdAaF5DgEG1p2WR5WdSVf7kdJp7iCVVqkyhQGtwyG61WTL9RUglgBYMasqolvHCFOrERFFPLTK8AIxg0Nq3rJwm1C09IKf6r2LQ2BbLRmK5sk57KAviicjKJyKl7wl43GeV9kUj+kzpRAxUNMWrVfBFTbQjnS/4DEZOnLBmkSrwyx7DX/NV5qwTLhVrjejrb9BHOyTGPDN5i/kdqnCBLwIJXLckmftisHmuTETaualCqUrL2vHFeNAL1mPdBIs63pDYqnBwHhFGqR3rt86Po2xPHY4zr4Txok2gC3YzcUyObcSfcSHQ+mEFMF7mDXDkoGbN51SiU0GCz6DbCDyMxSbGNTEMNx/dqtXMDr5ligSkdTOwtgjOcV757eTc4wXG1e9rXO89qYEX8b6ZzC7N6D17UoFe0JKPJuFJiMkSt/YR5avQuq/B8NR28RAxVHnD5i8WXrWByLLfMlz/BBt0MpQugN16P7b6YGJ/8ebS27rU5dbg3z06ePPMyKRIR5vFXr8an4ODwtxBk+NZddlFRN1FLlWQCjc77GxTeahAA7G22N50nbcDzbyzAJ/+stWAW5ptd5VZEdVnb3PnXjG5It8RJSPvldE2i1a1iGlV34jq2D1Y0cgoRWLEiSEJP4tJo8sDiFuslWNMithKj+pghroT3WLfMkp+5RaEHCpXlLpRl1Nq5hE631CDtvJhR5+G5aaYMD6UpN+8mbxNm9PFt0J+FgPq2DFdxj2qU9zDVF+RuUeZPom7m4/afBpM9Itd/vanXIdxwmQWGtls2YMcS5wqOGN921+taThWQfVYs6Re2cJkwF8jB5XAMOhJENJkzNJeOT7A/VzKbJW0F5eTdPk0JDFWILjiqM1YHRXg+XPWru8ckKBLkTc3rM4ByuNXvUVgq64hV0XgioaGkVd6sOT5gKQmp/E3HaX2NAi6XjI2Id7lIbNHcIUzsnf31cQy4p3U78arHlF00uUqDj0bY7kSXw7w/OnqYpbfMJM0+Ko/DgeyLrMjAv+iLMgp8tgKfddOEC+EJVG1C4y8HK9CJDWWLHFWyLMdTLTWQuJwosdh+szCvyrihFdI5DMzFoVVgCPp3crWJnHKZRroEQ92Y++p8sYveflPTZvdU6Q5zsoZZIJ2NxufIsJlZgVIurfOPmWr6u24rjfjo7UyBvTD3RSBVVafP8WZOeXrZh687WmCOoF83Ec1bd+2y6lEvz9qkFMd9NM07H/1dQr8kCyNgygKMHq1fyarl1SADoJKamLCMGO7ElXL9IW/iCb8snFLG53Q6cBMN8kaeyygA8/wG4kX0xskJo4ZfxCerlDBW4r7YUAFDbaJXBpFYnP6mAv20sY2bwL2jDqpU1xVzJA9WZzqLeFJhQ9zQ7mJ9RLykzX4x41Xs+8U7Jc/+vUxSC7HQu9GxVlQuBbQkIe9BKkunxIyYzY2KZA4ifwdtoD6anSwVNhKZgz8X1LLSzNtfHW86DG06PWX8ouGjz9nRK/0J4hIll+Cl+skJajpeQ/e4xvLKIuTKQpTr9MYJYlq2RgM+6VbMA4cU1hEGRbdO5wpzOnJ8j2ANx/QMBwjZrlGSTPhtrMsycnAshEMnyltiq0PQnWElt84AhV4pSiE/J5IdTR2Z/t9haNfOTB3BvOmEuk+AzfVU8jB+gCz4/NXti7+8DvzZqwyKUU3uOV1sH0rKMPdHFDSDrFgo
*/