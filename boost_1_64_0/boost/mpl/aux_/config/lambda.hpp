
#ifndef BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// agurt, 15/jan/02: full-fledged implementation requires both 
// template template parameters _and_ partial specialization

#if    !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    && (   defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
        || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        )

#   define BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif

#endif // BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

/* lambda.hpp
9Xk8+vytz921z70VPnWOreR5sprnzHk8t75/2PEuclzsbKnr0KNBN9DdUjHJHpaKZ/YCfUAm6Av68br5Q2Ay3hXHON/3fK4134i+/68dI5gf9RzhHI7zAzCvv1X7fnWgpe5ZB1u175WHWOpeeRg43jr8vfAYq+576Fd5/b+L1/3v8V7hI94T/AX4DBWj3cg4bTVjEdfJdZup7j3XMBaREvr8hucZGe/7LN5T2qa6/4s11f1wPO8XE01179eU94Eb5Z6H97TH8Dfefwbf+FSs6inGrrYxLvUL+Fb6IF4/y3jVdsaiDMapJCb1AmNUO3j9HW+513KJYDIIgolgkqVi4lNk/NVxbx3n1vFvHdP23F/t5b1U9HV7H8P7GbD6YyVdeG3dEyxgDGudLzoWGBn703HDB3yRcUAdR9Qxw8d8Km74hO/w9wLR8aRmvE9PBg5jAS08sYDWnlhAitRnfKADYwf3yfbyvsLP2HBHXuN34nX+5XJeZJz8R0/svIucywz3c0pLjchnBBfh9SZ+nu9nz2efdEzdYgxdx9MzGPPoyRhIb8ZIMj1xkP6MlQxk3GQwYyaOHIOMP4xg7GcUY0FjPDGcExmfmcD4zcmM9eQwvjORcZ/JntjOqZ64z+ngDH6WYxrjJ7meuMoMxq8KPHGrKxg7KfbEn1bJfgY3Sj8x1LOiWYzJN7fcuN2xfO7xIO9JN/Ne9GPPs5/P+RnOCkPdCyeD2KjPAg7nPZ3cz13Be+eVVuTnAPV34BN477xOxk3PffIofl7xFt7rttH3uZ773kxeC/fj5wsGMD48yFDXyVn8jvgdfNay2sD78z5/vU/dF98s7S3PCaSt+dsQx5kq5jQUDDNV7CkbDDdVvKkMzOZzoAo+C6oEVXyWNpefL5j/T3xGcB24W+bxc8ZrTcwzVUzyfD47uYDPPu4A60z1XKQ1Pze1hDHL9XwessFUz0Ha8HNUyxjL9H7W8lafG1ceY6hnZOP4jGw8n5edxGdkp/CZmNx/vMjPf7wEXua9fY2p7k9eZaxmpye2/SZj3m+Z6r78HcZ43jVVzPs9xkL2MDbzIfjI83zmE/ApYzd/YRx7JmM2+xkf+oLPAg7wnusrU8VeDoJvGG9/xFTPJraYKsbyuKni8ltNFYtfbqrYx9OmisM/Y6p7uudMFad5XuoxrvcE44BPGqjD2N1NhopbrPF8BvcqcLX+fK7nWeXFBp9Rgks9n395iM9zH+az3b/x+cyXvsh4s44FPgue07FAT2xwh/RtxhZfYfzxz554pI4/drJ1PNmNd77BuOouxlPfZlx0N+Os70XFQz8EHzF++jHjqp964q+fMc66n3HYLxhTPeCJm37N2Ok3nrjquYI8g2BM8wdPTPQn8LMnXnqdoWJhqwz1rOgGQ8WUjjLcOORjlvvMLmPZ2GXfNVNTUyU+H9MYlVo2Z5umzvh0Rs+KMXXGCgbtoG0F7digHRe044N2YtBuEowPV47TaVj4dMbSGVtnYnQmlhlLp2aPJMsXK5MEmcTJpHmPWNM2LxgSF15Dyye+hUySaUIl47mYBJ2aOuPTGUtnbJ2J0ZlYnYnTmfDyEqYvG2suO3QCE5NpaDXa61aLkVfNZNJUN1sTnWkquoOubuqMT2csnbF1Jk5n4nWmqc40028fE0wLpiUF05KDaU4wrXkwrUUwrWUwrVUwLRBM6xRqtt8HTV8w3ioEBUE7I2hjN/ZIuKrrJVd/1bPA7BlM88uaYcfGBO2mQTvUZ749N+6ERJ2RbXk5y7akWJrKmz06Wz6ZWOEdEm4px4oPpnXBW8fExKmpxcRk6mOqvc00PrS+Fw72ma3DuTbMJaK2zlnhnG4r2wymdQimtQ4=
*/