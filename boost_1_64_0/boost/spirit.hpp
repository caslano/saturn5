/*=============================================================================
  Copyright (c) 2001-2008 Joel de Guzman
  Copyright (c) 2001-2008 Hartmut Kaiser
  http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT
#define BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT

#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message ("Warning: This header is deprecated. Please use: boost/spirit/include/classic.hpp")
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning "This header is deprecated. Please use: boost/spirit/include/classic.hpp"
#endif
#endif

#if !defined(BOOST_SPIRIT_USE_OLD_NAMESPACE)
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif
#include <boost/spirit/include/classic.hpp>

#endif

/* spirit.hpp
A+RH4vybuLJZ7Rx1aGu0zn6WAB4L8lryYltZ3IslqC3StcDFecVhrN4h9y4iIcCLkrhAqL+c6UhmF3u0fO0KHmh6xXNoV+NGhWzra99cEI5aUcEGmpUZ3UT26ws+67u5X0ZFU1z4mJx3s5Oigo3UR81lUZMEGyaC0eDaxU/uLzPC4zdd3hmYezLmib5W1lZSIKwZYc/swG2Ok2tLK403u4AivAi2FibrKXPVvl82MwEnTulubsb3N9JHZTM2ubc0KhM9bkqYjUaagFDIKPc4lfeUxgQbo1nWfbujLvIKOCk+BTcDdHWgpnpqqEbSPBnPqyggManiNRL9TX4PzAPJM9qSFE33XPymuhLHdHmy86xL0dA8VPHj7CfPKvEaovtrcCMBDnxDShRYhkU4CCRWPoV0jEmbLG19oFa31p31yu/SsrMPVtbMYuT/6+PEew93Zcw/10Txg17a2smXOLCDW6otPsdGrYH1njjZ+WRr1aJPolhWquWtHGGzOAMsaYx1HQruYnmMEK9K6+3E7K3qoFDFjbBXoqabdvY4ggIF59CT5DVgPZRKbOZE2FTS4eIn5PL6rClZXVbY1pL70phYDhcn0N/eHdG2bxntc9wOgbGaDlvbJKAhpyHoFX7EY5uySGBDkZv65GkL4i+30Menh+IVnraQbOfwWGE7o0EQj8VOz7Y/WZ1pi5RWPMlDZ1SuJtejE7T+62SeNsXMEv/kk/Tm6IrfK7ZQuZZqyn+V7C7PLJbvYcrHsPwHLB9lyr8QVp5Z4qVqyjO6nmScZjIeqK/Jzwo7o7PJqGUy/mxnPGa6Wl5PZ9xiZywxGZskI38yE/X1vbN6VaeNKG4bJYVwhF+i/qoTA67EZmqRTuwWqp2s5ui0ZFfBWDVBJya4nE7SSo7CIek4Pzb+/fMct33VrjMphToRplV0LTCqfOF/i3iG/RU9/1q91uGQ7/nU3OJL6EOY/afdke/TtrMrl5uutEHrQ9G63Rn2TAdp6zNRdeOB9WN5I/O4E+z/8KsWfqUIB4t9C1vs6QnaX1f7H+84T98bCqalR+W30kbYjzVxjvlzwKGnEw22a1FyO9SB7fWZCbS9Jouw2pCD4WEOV6yxtJHo3T5d/1t8sshvXjDULfxP76VnyDgPxuOJ8mxwmD266YlKrbpmp97WENKWfhOxbirhNBEmhoTWI0lLJnhyoavxVs0I8HkTvm8QsK5OIgc6DcE4Vde6+pS8Kdp497OYz3pf3Z4rhJkzCmYkO1puLrA/jTYVeHuG/z4S1RW5NvNUIfLPBpR28lStuJDepTpijEm67iwdWzEgryktixdXuOXlfI2XAsAN6g9ZAixTNcBZzYRd58qZnYnEdJWFpnyVpXjrJh2kexLO9XTDKmXuKfUmzn/ACTJwkeEmLKQ49vo63sCyHO2fd4bu9DRPeK/Prd7rl7rrXuuwAgc90uvnXL3e2sf0elhT3euz3L3+Q47Ta5neytdVMWBwBFkZnyXetkC4DnlxAsvivJPgrN5/rbQosj/smJ72pjeBBSeeYXZ9VWS+sDBEgM4BV54GXyq/NcvDecWGn52CqcRaFtWRvd7RxFf9qT/Z3DUmiOI4HQXiLB1d9fI6sjZg6vtK6BghxKU+b9ShnCqxt79ef6wfoXd2/Ose4aTu+lQ9aBoOTlxwCFIXaGubmfvZnRGrbZpXv0pqX6+4APQY5s0XNfoP8fp2BEp4bW2Znd6JLSUF6PpeQB+300gBOTc0dqlvrDOj8oDesSCMLAwimFpbiODrQgTRhKtZFv+cVjtMd3Xot2GWQvH/0mXmquhOXsqrqjs5M+1wuhPzPq5RXZjHKaAw8YrqAj8PpbpAVg1UF856J4c=
*/