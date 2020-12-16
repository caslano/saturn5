
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
Dw13yoZn5nXaYudJPg35EOs4QDPH7UZCgipX11hHf9PTyPxaPT3ur2ctAu+tv0SDJ2unwbVAH+k/B2mZeBVerVxM7ZPj2bzqJhTtb6dxy1spauEb5tMkTAsK7LHuRwCFXq/mPxOS6W/WZz75/EeqEj/Hul4ZYuI0Gy7V/gbLvtdQz5LpOD/2PN3QnoDZPyy5kGC+lsl2shk1Dyi8QIVLjn5Bv6dq8IAx19D5RJhfy9ZC9KmhNO3SYgrtrIab+iVsvqrMAjqCYG/Wx7JGCGH5mW58nCEDyfzb7L7cUyoRcNdZxXcohd+ihMMLkPNfHS9YrSngf7NYlcpLGJZ0oySzEBm3b/NPYxnONDhjIG05Psvb8I2xd6C5MBGSb0eQf/1LBGeHU2nWKM7yHpCajzOzeGSK+yl+sEhyxmyTCjrzz47cfY258B9d2qw6g9UMqYe1ZxI2appg2aRr7F18DZlt8selKU8oTiaQLQp9BH8tQ6qaYS3gdPak1aeP+y3z2TDjFBqz7w4/W2pEj9N82Yy6SKrd95f9dPLA8uHWWL63kS4vHQVTrXraUvoPBhWx6Kt9ww4dZZiW4IbJdzJoib0qBSuPh13ubLZk3XaceGdEnn4Cxq6QhFr/lxCqq8DpVV+RtC2ZHw97jLTjSkzv7lj0/33ClBc14svtOZDucIR6yHlmLtyBqlQ7vlJmI2b+Kaa6o1cRtUQexh5a0FPazJqHZcKh7gYtcllOBWFP0TglhPjDHtaY1Iipdnf5w9kGsLPcxNK7jlG62DJMY/kYnXyHegVc8naLGdNh6VSqFsUCg1bQze4qjI/0QJn/MbZyzXa8u5nMwsxm48oBYZoh9JMqaYAeLl9D6/5sZAMPJGiqaiP1zPtL4YoqzOPGMrKbtomsO67iTIYbOfvGk2RZJf9kUUz/hJfBQigfQhNSacXz2SQvPR6egRtpj9tw9nJDADITF9BYo8to3baINagkwFdZmX6ozUecBMe4YIEOyflJq3ul8aP5FCWpOiHW5i8dXdOHXyKXeE/jVaqOS+J//aNo1N10ipwZT1dvyfFfDjupTsaJSZR/hf2NJzwnGPTSdi+ZBDyjJN0T3C5dF6pVCvj34CYyDVrYj1n1KG0XYWcEuXf0EWNalWOBed5v0XllByKXrOYR9cqkWbGSXHMCadrjo7xwvgg9KPksYJ6riDYHsoGzbbDe5sPGGK6G9+lbOGy+C3MD/XEl4QaZzt6JNVfnYcYYJ6o8Y001ubI8aaEq6nb40ilxLRS+iKMXh4vJbtNHlleWSsNHHeN177RoiuMb/tfuCJoahjK3pcOpNnsLd/KRQ1beW/L3C0X7ooe0TE0HV/bHUc1WRk5+jbgz4SkKrdL57zP2ML+qxnKtw+A4chtdOPKADpXmQTg/Fd8jR/D0n9rocJPgNu62FPv2JZ/XXo7nPqpkG+eKZxmK7ND4udR/Wh9Ow9ypXPUJj26bCrPXe/hgUwEJab5lyjbzUD1dkeJylGBxPJtdn/0Zlvo+3O3Dcxx7/ZOSMgyIzxvCBmKeYYunJN45R1O/QhbXv5FPRWvWUqGMPkaMkWAlRhtoR9ELOvHLnn4EutGbo+10dpQmTatxp8uPtHjnqEnQhTWbJq9Eh5g5Wf33lV7f1GQvIjuRn7+EZB6owGTjNaa8oQK/w9ogrWKEnycX8Eav6dR32Jwd93bBff6CDftmTI6JX9nfiSnw7DfnW9JOYcMTbSSeeopdC89wh0lfUNu2lI2zXQdIRcB39HiILlhEY00CkDhVE1uiXKn+SzsN148m90MkOFc9GBi+hlXWpKNUcQMpeSQiy7oEB3/MoVmZcXzu03AYmUnBOyIbR4tsaLTRHHo=
*/