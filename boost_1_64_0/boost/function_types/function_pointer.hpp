
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_pointer
    {
      typedef typename function_types::function_type<Types,Tag>::type * type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* function_pointer.hpp
uK06fF7BfT/NbrSJMjhONaSm0hehNXLp4jxE0oZ1qmktAnmEjVvE78f2fA5iB0+vLnsfc+SmvN+Xe3RLLu9j3iouzzNfMe904feSPPXBILxf9moudNeF3E2evnp9Sen7kTfl/Xtuz2i+3MOO9XmPA9U71l9eP1+ePoYFqf6bpe+jns6np7v9ZP5+D+ofFRw2K7JX8R5XrDY5nb7nBccTpCEMQeAxMr6M1oEBGAGOI4QkBKdt52vc82998rwfbcdHkXGA8uPdKTgWBw+KTEQ5NGAB9Jaz3hiLQ1eknECnr4jSUZlyPD0CZtbpLCjGA++8oRsrfXVO526xDj/lOPAqSeMZOEmanllznfqmeHpMzj1bohyqrOzYIMWje3ChPfA6owceXRnP7k4LbPj4vDMrferQ5d+EhjVjjBxYAJbuLlfAY4RZQHQ+Tsu6fSRg2uj1FSeIpwj5+4E83nyUok0UXiYkyoIMVvHBMXru2W51HpbXWJJ0wnl9s9vvu08eid//Ij06L8iiTYQn6aR6OowBtfN445PTGFj6qg1Kyve8hq2Vz3M4Tn5sEeSXr7dwfutJbSf/5egy30ounlV4K37ZdO25/qMh6w6/TrnrjCPvSv1vzmNpOujpv3edwj5zyl99j19nPcKYrvf+t+rzzwpvthuzp+GI/CGOlli6FovFGURKtyQmNG/aNNCT3+2PcikP12pCkZ50enL4LfS3iMdz56iOknGKaa+XRJ0QbP+D19vB/6P16vI/Wq+0/9F62SgI4dkufh29G2PnYRwaHy3ijLPLOWO1whmbizvjB76+Tj/pwpfm+fn4KB8/AJ6PccZQhufn45yyPD9PP+rD85V3xlkF+HJ4OdN9fP+pfvk/LeTpZ60aB3jdEZBvBgibAG5/3EiyEcBf+7dxXvPT46WRbZwHqXvxcVc+tvCxlcZ5hyrf+Dv7sYb369/sQ3UkdGqDCDkH8r4eX34o7+u/6RXzZye58Snp55t/3+hN1785W7zTK7xhf8DVrhsPieme1/EHcmm/7L9Kfw8wkk8nC+P+X1Iflz7Tf5Bez2d46PP39adne/1r+su9f3SwjvT3vw6+Xf3+U4JVWK/FRoV2dePRJ/CXwoKvQES+nv/l/ZTXHQyUI96wkOE9NzKwHNdGhnthCjTkTg+QyovVit5fRNOi9xZhWrJxgWnJxgWmvW5cIF66cSHo43UDA/klNUM+jw0NCV5n9MQLGxpyvIydyqOVlqcd9aA1lfS78KSpyaCN9aYb3fdAAn25lSgt2wih+yBprq0FYX/D9f5RvKSQ4oVNCsn7DzzwaXTTg16uuPfnHNctrN6KDx1acQMkWWPEDx3/CKLjKeI0EEISKplfu0XWt3q/Ep/vrd/LxOejNvQ272Vy5TPRB88913sKhOlDnP4zLsUZswapP1VbpekdNmnaLOPPSs3f/Pr3BrORXxemvZu8/LSbtyttxAsXvo67Dt7waZTiiU/Vvp18i6d9aQ2JCQ7B+Ei+460fUjx98lqURovBnT6LO039kuOZb3RrOGQ8y7UbaQk0LRWCaUoS+EWF07T3whEvFEr9SISkYEy78tBHygXPKfBTVyKk6UsRRGkch555Kd5gitc49DaloCsT8FQdUZpWREh789cU73jDQ3ymRqu1SPHWXOTbzfiWsUSgIR1nLFpva2Yqn5bogWlJg2Ja0nBD9cZmAV76neL5mroqKuCHmPS4tSOk5eVRiQI9D/ugdFkLCHir2aC30RwSvFAD+nsAFpOBddzF0xi1/NvJxOPK5P59B0ceF02XarZlso7WxUdWLfYE2ePUIH/lsqsf6EZ3vD7JhU8w6DRGu5nfW3K/McdDDz3OjxYLvjI=
*/