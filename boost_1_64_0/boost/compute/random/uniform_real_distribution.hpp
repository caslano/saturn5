//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/detail/literal.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class uniform_real_distribution
/// \brief Produces uniformly distributed random floating-point numbers.
///
/// The following example shows how to setup a uniform real distribution to
/// produce random \c float values between \c 1 and \c 100.
///
/// \snippet test/test_uniform_real_distribution.cpp generate
///
/// \see default_random_engine, normal_distribution
template<class RealType = float>
class uniform_real_distribution
{
public:
    typedef RealType result_type;

    /// Creates a new uniform distribution producing numbers in the range
    /// [\p a, \p b).
    /// Requires a < b
    uniform_real_distribution(RealType a = 0.f, RealType b = 1.f)
        : m_a(a),
          m_b(b)
    {
        BOOST_ASSERT(a < b);
    }

    /// Destroys the uniform_real_distribution object.
    ~uniform_real_distribution()
    {
    }

    /// Returns the minimum value of the distribution.
    result_type a() const
    {
        return m_a;
    }

    /// Returns the maximum value of the distribution.
    result_type b() const
    {
        return m_b;
    }

    /// Generates uniformly distributed floating-point numbers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        BOOST_COMPUTE_FUNCTION(RealType, scale_random, (const uint_ x),
        {
            return nextafter(LO + (convert_RealType(x) / MAX_RANDOM) * (HI - LO), (RealType) LO);
        });

        scale_random.define("LO", detail::make_literal(m_a));
        scale_random.define("HI", detail::make_literal(m_b));
        scale_random.define("MAX_RANDOM", "UINT_MAX");
        scale_random.define(
            "convert_RealType", std::string("convert_") + type_name<RealType>()
        );
        scale_random.define("RealType", type_name<RealType>());

        generator.generate(
            first, last, scale_random, queue
        );
    }

    /// \internal_ (deprecated)
    template<class OutputIterator, class Generator>
    void fill(OutputIterator first,
              OutputIterator last,
              Generator &g,
              command_queue &queue)
    {
        generate(first, last, g, queue);
    }

private:
    RealType m_a;
    RealType m_b;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

/* uniform_real_distribution.hpp
z4DquP7U4xJRJaYQInnh3hR3rJlbNnW9f8Nc3GZTnK4b714b7xoGTJ5eVfeDDa77/GDgkjI7bifc1e7F8w6u1m9NYK/qMYGIoFliTpLd3Wb4vjhbLLAQX34uDzFREvfctNgcz3lenUFH5y2nPKtRLF4w5I1COE2yk8YJTyfcNI3PTs9OasLdGn8w3QX+7rAnP3vAO948jqmd8ReTyWe0mPc+KFhOE1IqtQmk5aHvn8TDfPwBnlueqUhLWbkayNN9CJPY67iGvnHSCWp5JrbsNP+EChvjKxLwsZyxkC80GqWMXfE95a7TU/A0Wa+ZH+Hxll7YrAPQ9ajb4J/SY7Z1Ns5npVY0LUDAGA/tb8P8kFwIrtXCARAU5/GHHeamc5a7FoWxuQltlL0PKquattJpQdpqh7IQb2guCz59jnJbkphvVy33Wgs8XK3GYEBbf2MR1pCS25szRgHbFOHVzt7ShjdV+OgvYRBetwCGtbdFAHy11G/C1/jDgd8plovgBvDnF83H4OKgzqyTk5rzeeB/08CfqZemBN7J3qLan+/XXaXbiCjMzRkP67bZLZ3Sa/xdlfy02UA21t63B25Wgm/XfMDedQrZqrMVIDv4OiC8J9FrXv+zgK/+4ZCxDLy5UB11st8bx7xkxTAV8vV1gCUG+7z8CMsRtBOalnUfvGA1gKW9F6jtGMeQDHhfrFUsmDvgz8cxeDbCS6JyzrxEwDf7Wwv3fX5Y/S0PBl39wB29MNx5tWDhIF+37eceXZyMbf/Q2HbOTIrWr8d/hXv67tFkAx7x30R4RXjgzmllAX9W9Z/F23hwCdkM0Lm9xweihPaapkbfxH5e894BfSDcITGGadOiCpcF06Y5YCDmztDHTkTPbZGIqP3Q+XawZX/58b2HfO7eh+ALxu6uw9efXWz4lj0G1ZGJdr6UUAKqo12+SnXEnUPgd4IQ0H2jehLJyZtIc9moh67shXma+OuzBMTAQfUoopUryVmN6zk73m9bphUbedE/hfCBaMOqOCYiPBwcm8NO3YaGs/C3hzYoo7ShRqKB3L7r6rm32urZzCP6J4QXREpaWlo9hJ8O0bBo4bv6zx6biLcuJ5boOiV8TZY45tu9z08wX6DUZWbsGnR6Bs77w3n7oQhrK2EWifHYER5OH5vNVGZw/iN9HZlkpkthmuIqzs/Ox3hkZcaBjS0mWSS1oGWrEf1rmy+7+bYL3yeE1aQUa1OOfo09mg9XyDln/X1CeEWsoCYJjvHTsbU0XfbGGH9paHsIznMj0xq/Xy83Tz6oXT5zdz7gA7eWjhqm1tAWXfZyd29aa/tDPtZhrOtQOSFi6fpsMjCks7X3H+gJAAuxT0xK3AC2eSgfnTfHCID3ffbgn+J2m5A55a5r+O7+PsTZ2FwXtxBekhZezKmuyw6W4N4ll+GNeRmwvrkHyKS7/j4YwTBXhnazmAW1qeuz44vdiqrxX067+Alwl3pTjy9ER1GcF3kNrzcVOMF1591P/RSvC6ttZg7DnhxwW78xtjVL6lyy/Ri9qH4K4NgxtPVHuK2F22x94gCH/WdYi38Z+pf7qGIVtAPOh5ThXcJkVMFY54ML1nbzqrb14iWlTky40MGcmrGwFnTgyWvo3GnjCEenL3hydSY/27xn3UJ4TaS0rjabbeDx4FL4biF8CxaljXAZJiUcNNoAN8/k86tdWBrdmn4VqkcQqwMVXIVZs9+ioVzUsN+7x2udxy7khB6wjAoXbVGguW97yUF+Lju6uDocsN/42bimlBKsuDX2/Hh3D4NBR9BjM3GRq1SUWEOfh2yVDwP/AcQZiY9a6kTZGri3Ct5dLYA1FNhL635wuJh74Hz8c3zGZi4mq7k=
*/