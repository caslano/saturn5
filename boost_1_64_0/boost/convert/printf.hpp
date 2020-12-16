// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_PRINTF_HPP
#define BOOST_CONVERT_PRINTF_HPP

#include <boost/convert/base.hpp>
#include <boost/make_default.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/range/as_literal.hpp>
#include <string>
#include <cstdio>

namespace boost { namespace cnv
{
    struct printf;
}}

struct boost::cnv::printf : boost::cnv::cnvbase<boost::cnv::printf>
{
    using this_type = boost::cnv::printf;
    using base_type = boost::cnv::cnvbase<this_type>;

    using base_type::operator();

    template<typename in_type>
    cnv::range<char*>
    to_str(in_type value_in, char* buf) const
    {
        char const*     fmt = pformat(pos<in_type>());
        int const num_chars = snprintf(buf, bufsize_, fmt, precision_, value_in);
        bool const  success = num_chars < bufsize_;

        return cnv::range<char*>(buf, success ? (buf + num_chars) : buf);
    }
    template<typename string_type, typename out_type>
    void
    str_to(cnv::range<string_type> range, optional<out_type>& result_out) const
    {
        out_type    result = boost::make_default<out_type>();
        int const num_read = sscanf(&*range.begin(), format(pos<out_type>()), &result);

        if (num_read == 1)
            result_out = result;
    }

    private:

    template<typename Type> int pos() const
    {
        using managed_types = boost::mpl::vector<double, float,
                                  int, unsigned int,
                                  short int, unsigned short int,
                                  long int, unsigned long int>;
        using type_iterator = typename boost::mpl::find<managed_types, Type>::type;
        using      type_pos = typename type_iterator::pos;

        return type_pos::value;
    }

    char const* pformat(int pos) const
    {
        static char const* d_fmt[] = { "%.*f", "%.*f", "%.*d", "%.*u", "%.*hd", "%.*hu", "%.*ld", "%.*lu" }; // Must match managed_types
        static char const* x_fmt[] = { "%.*f", "%.*f", "%.*x", "%.*x", "%.*hx", "%.*hx", "%.*lx", "%.*lx" }; // Must match managed_types
        static char const* o_fmt[] = { "%.*f", "%.*f", "%.*o", "%.*o", "%.*ho", "%.*ho", "%.*lo", "%.*lo" }; // Must match managed_types
        char const*            fmt = base_ == boost::cnv::base::dec ? d_fmt[pos]
                                   : base_ == boost::cnv::base::hex ? x_fmt[pos]
                                   : base_ == boost::cnv::base::oct ? o_fmt[pos]
                                   : (BOOST_ASSERT(0), nullptr);
        return fmt;
    }
    char const* format(int pos) const
    {
        static char const* d_fmt[] = { "%f", "%f", "%d", "%u", "%hd", "%hu", "%ld", "%lu" }; // Must match managed_types
        static char const* x_fmt[] = { "%f", "%f", "%x", "%x", "%hx", "%hx", "%lx", "%lx" }; // Must match managed_types
        static char const* o_fmt[] = { "%f", "%f", "%o", "%o", "%ho", "%ho", "%lo", "%lo" }; // Must match managed_types
        char const*            fmt = base_ == boost::cnv::base::dec ? d_fmt[pos]
                                   : base_ == boost::cnv::base::hex ? x_fmt[pos]
                                   : base_ == boost::cnv::base::oct ? o_fmt[pos]
                                   : (BOOST_ASSERT(0), nullptr);
        return fmt;
    }
};

#endif // BOOST_CONVERT_PRINTF_HPP

/* printf.hpp
sKJReTAd/diLbby4mrwXNpD9OGXZnMFasKgycQl+cunD8K6DcDFk/IbQK3LRgb39UAx42DpwEa5dDx4551PiGmKRLu9xxpxD5w/oe4n4Gz8wfQuYUhVcpm3BUHgqv+/D5/+CbDI/Yl0/IdP52PijnO044q/z+JCXwZ8s/C/+dAP+aTFyP1sTW8QHFL8IXt2LrDfAj9CTnClwzJf9ESQxxiP0Jda6PZg8M3LbXhl+AO5smck9VS64y3qSTtCOGDUZmfjB3S+1Rd8G8D6hCjwC7lsbvW9FXEg8xn/fnbifPX1En8Z3oT/v4vPJNeCybHUnoI/4iS3niGlXEkejF/98lLNCdl8exIeTpyZ1A0lGJuDCYTD2T3jwjxXhQfDNjuXx68QW6zizZvDW9sRn/jPxVXXJL8zGv6O7z6IHvbC7MehXGBxkPrmJpnfApdDZuBh8WiN4Anr35mDsGZuK34BNncI3Mfenzcndw6//Ad7W74A9H8DP28jzbCIuacG9Prh+9wxwPZM54WPNexEXfwfGYUvvxhMjBhLHwQUeqY5f6AWfJY63B7F+ctYv3Iae9QAHlqCTuzhnxvqenPcU9rULjn/6Grnk8uK7jPGhsej6V4zZhbiV+b7gbdts/N9zT4Db8L4ej4H95Ivap5LL7oT9+aHjyPxxuOhX2FPFzdylgJ/z8G1TyW0NnYq94de6FpM7OIie27CTk4wBtwueA2/gzB6GMy5Hn+ZNRXew7VM7iTHIf0fPDSC3jS40R+7EGG9sIefRHo6HXVYgJzCZ+5sNC4gdkfVOdGsb3Kb8WvCRf4v7m6/EPXAV5kdW3d6AezQhRiHOPT4Y3shdZUV87EnMowrz+38CRjTEX7UFZ3O4j3oeDpnD/dZKzh/f8dS/4FrPYbN5+Jb9+FSw9blvifHQo9uOi7tkfAy4GpeITyAu//Bh+BH2uoQzWbfNBk9jTWuRCXfWZwPgX8h1HzIKu4584RjL4EOfBIPrYLm9kFzmQO55P0MmdTk/7O5XZD4D3WkGZs4Gu/PBy2XV4V7oZB3ivYFbsKVx/D0PHz8S/0sc8+LrxOz0O4jf/HIJ9rkPfEWGLXYTJ9rglPiT4XC3J/vhE/uDKQKHk8DP0awvHI5GbHQRHZ0+gD2xrsf/iW3g1/pVIGaGXw2CV617iPVjw2fAq97YUnN0OT8ZjGedRcRJ4jvoBr/DXshV+a8nH4FfG1SEv8VmAn7xA0PR8+3wui/hRfjZptyhTUMu04ixQzi3e6fD+3oSW2wmDjxLvP4xoVcKOY9I/CvxYIvW+PuPkPMg9B+unNnXj7gDrjIE3t6JuAE9ajkEn0b9t0+zRnjRgunEFMtFbhFcYA9/iXcpYNdksHUoWPlgHzDwZ3RlKbLHXr7jHZlfHrb0JpgCD5uPLmxNwIbhOI+CcT/j6yoHcQ470Ethj+j/mg7oZzY8Dzu5dhA7/gjeSZ6xAVj2yJf4liywHLsZNoHxConRmuGvniV2wsYcXdHBY+RYXgEreee+cjk4VoyfY29P98IG8B0t/eBxLcHrz+Bv6M6423lTdIl++M8VB7nrqA8WoJOj0PlM7GQKd6CX81gzsvrmR3Jaw4m7Ezkj8iZNnejTJeT0Nbwfv7EMnzDrB2K+OrTbS6wHXnzJ+oM/x4+NIW4F96fA87rM504OPuMCs65wzpPOwpEWYRdwsiuJxBL4zNXtsTN8xzD0OD2ZtVUir7+Q+sd5h4XfWYR/OQ93+8cu3rrdgQ/HZ31Ljuk0/KMIHTyyDx46Hx6MrD4nv7KQeGb8UDBqH3EDmPTxbPYYho7tR1fhb+kd6He3uN8h93kcjGyNLyRfMmkwXDUQWUzjnXYEOIFevfw=
*/