// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_ARGS_H
#define BOOST_MSM_BACK_ARGS_H

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_if.hpp> 
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/function.hpp>

#ifndef BOOST_MSM_VISITOR_ARG_SIZE
#define BOOST_MSM_VISITOR_ARG_SIZE 2 // default max number of arguments
#endif

namespace boost { namespace msm { namespace back
{
struct no_args {};
#define MSM_ARGS_TYPEDEF_SUB(z, n, unused) typedef ARG ## n argument ## n ;
#define MSM_ARGS_PRINT(z, n, data) data
#define MSM_ARGS_NONE_PRINT(z, n, data) class data ## n = no_args                          \
    BOOST_PP_COMMA_IF( BOOST_PP_LESS(n, BOOST_PP_DEC(BOOST_MSM_VISITOR_ARG_SIZE) ) )                  

#define MSM_VISITOR_MAIN_ARGS(n)                                                        \
    template <class RES,                                                                \
              BOOST_PP_REPEAT(BOOST_MSM_VISITOR_ARG_SIZE, MSM_ARGS_NONE_PRINT, ARG)>    \
    struct args                                                                         \
    {                                                                                   \
        typedef ::boost::function<RES(BOOST_PP_ENUM_PARAMS(n, ARG))> type;              \
        enum {args_number=n};                                                           \
        BOOST_PP_REPEAT(n, MSM_ARGS_TYPEDEF_SUB, ~ )                                    \
    };

#define MSM_VISITOR_ARGS(z, n, unused)                                                              \
    template <class RES BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class ARG)>                    \
    struct args<RES,                                                                                \
                BOOST_PP_ENUM_PARAMS(n,ARG)                                                         \
                BOOST_PP_COMMA_IF(n)                                                                \
                BOOST_PP_ENUM(BOOST_PP_SUB(BOOST_MSM_VISITOR_ARG_SIZE,n), MSM_ARGS_PRINT, no_args)     \
                >                                                                                   \
    {                                                                                               \
        typedef ::boost::function<RES(BOOST_PP_ENUM_PARAMS(n, ARG))> type;                          \
        enum {args_number=n};                                                                       \
        BOOST_PP_REPEAT(n, MSM_ARGS_TYPEDEF_SUB, ~ )                                                \
    };
MSM_VISITOR_MAIN_ARGS(BOOST_MSM_VISITOR_ARG_SIZE)
BOOST_PP_REPEAT(BOOST_MSM_VISITOR_ARG_SIZE, MSM_VISITOR_ARGS, ~)

#undef MSM_VISITOR_ARGS
#undef MSM_ARGS_PRINT

}}}

#endif //BOOST_MSM_BACK_ARGS_H


/* args.hpp
l66fbBaUrp9iTlN8S8t2lJVUV4J3uCXmVUqrSrIt2ENtKSmycu6NTfkEylgPgDM9TnUszXFuAFs6lNuaYzf+e88kNv7eLFu91lSn8XXU+EdE4+uGcj/FNsXWnfZ0wGp21AdPCwbfa9MGJJJ6lMTt6Fh3GtnhNauW+P2f98ff+wKW//jT4nQdmMDOp4Xxw+7ukG38/Wj8t6Dxu2DcXOzLMEFl7w3l5ueIv+Q6/51x/isrLsD4Rs0+gGcPb/vsrwBiJxa1vZN3AQ3PDb14w3bxGvhFsXfy8ElLHtc359ZVxHq8Lti/9NOJdtjfXPIU9Htgth86uhv/Qy5igDymzD9mTccU8DQzIdmc5N4tlWSia+3D2Rh3pOBXYb6RCvrBw7cdkWNLs0Cl+9oeyZLM0tiGMcVHPa7foPylN6Ij7ckGp4xO7ILSOee9c+P5Uek30R+7DsEe+QPjU3qCB0/VC2EtHT+vn9juWPmCvRK9N/Yo3c39GU1atw2+gmcFl4JzWJiVrpUnklt5QrRy/K6P6ETFCfyn0a5DkhhnO5+lHluaXbo2bzy+i0GqiCljYhFknud1vedxfQlVVMVujr0Hu0FP6S2oAmphaZ71X8Cs90MXLmkneelq5WJxtRKvVH7uiR0byv3PP8J7QG9rxtdUgYV1jg3CEU7/GTjCxuIVVGB0XiktRbO4Ad0pGvjNsCf/B3H9AxSU9Oeeq3TP+J130bXje3Cb9ovBUzipDt3xIPAauiNI4WoKIxQaFJoUNlPYQuFmCrdQuI3C7RQ+SuFOCn9MYTuFuyl8jMLHKeyi8AkK91D4FIV7KXyGwn0UPk/hfgpfovBlCl+h8ACFr1L4GoWvU3iQwjcofJPCtyjspvBnFL5D4T9R2ENhH4XvUniYwn6hh1EYfkrhHyg8T+EXFF6g8CKFlyn8msJvKcR3eCafiVm4SpjuWezi2IlY9sAvv7wy1IV9B67CSW37R9zTwZLpbfqD7a+zhobnGXj/TJqS4o9uf51QILlecedcRzqGoqh+jaLL0xUFb/9FM56XC0KLh6UWHx3IS1cK4qV08W1b6yQzG1I/dKXIkqS/4qM7SkDNePt2rFc4iaTm4BOVBl5wpVRQ5CTt5KSi4aUCI5daPnKpYteIWs0bOem/M9Mlka4/zEwnBr0C6khmihjxpNcy00lIdf0k8+qd+9DIsqweuSixnjty0VuvUes3GSOlw7qjTux4PounK52jynPoKsCSHXR76D0Ag89/fGVI+n/3OdaXQfgm4x7GFkY/458yVjGWME5n/JjR/kzqEfQ0xhLGKsZ6Rp3xUcbHGZ9hfIXxLcY+xuOMpxkHGC8yPn9Y4O29AmczKozrGSOMP2bcw7if8TXGbsbDjL9mHGC8yDiO9fAq1/8mYw/jScYPGS8wjj4icArjbMZxzPf7hwRmMU5iXMT5pjNdxric8UHGdsZ9jAcZjzF+wPgHxit2Pe8KzGecy1jBuJJxPaPOuJ1xD+NLjN2MJxkHGDN/IXAyYxnjMsZ6xgjjNsZ2xr2MrzP2Mf4z4wDjZcZxrPd8xoWM1YxNjNsZnzicbN/nfy7oU4x9jM8zbmH0M1YzzmOcxpj984zvNE77PRKdVFHaBdZ6BV7Pp+G1rBrSOfxCOEb2ZUi3dwlunuia8Ka5c6qNsE+LRiVpo6RJhqRDGJSKpdkOjxppueSWlkoeqVa6W7rbia+G3AHIb1K5aikMoSktgbggxGA5XVKlRqBNSU4oWQupPqkJ0kOU1gRxD6TNL6fUASt4yik+K0EqfFjYGsoRz5lO7griVwhYBV9MwzhM90qVQBVCvmqIkaRVEOsB3iI2nj/Oq5p5eShn/CNKVkDZ1ZCqQLnqYfGr4CjOdbicNm9bmuF842WXQ/4fShukFSCrl3MJftXQe/eyhEtGkE+UsvlUQ6yHjuKlUJsNCfpeC7nmSnPoWE7pr2oohWmF0E8t1PuSNIt6Gft6I9OYP0SpsyQrbkdG2G/5zBorYFLBmtaoqYUeWGwZhqabi8O6aYSDNZr5AB8+wAVWRMxAWI9KtZoRihrN7kjEo0dNNRj0hv3IKNWeCyU/HAXjetfMkYoKO4XEgK4G5RrNaNYMabVmBBpaIYxCtR69IewW+e6tXLm8sqp4dmFFFXUM5ADWIKw/gAJ61ahov276g8FC+MHxDHo8xVLNXBIO+jWjWjWb1tj1RkFrDTCagiAvtiBVbjfQfme8wTwLRz7QbJDGix2L/eWTmqGPw6AD7KMwjSDw56QRjcZUYv41nuU11StWVBVWrFxNfnZfBvmd6ruF/9lfIbBe9cugqrBPxeYJmTLYx+D53iyWc3HYqGwJmI5/CUHLfFSfBt94qwywBRy3AbINmdpsUD6Z+IyVRrPfqAKrrYFvYh47Fe0RLXfpCKnY7hWgDTflSpdnJVhwEVhKMcXMhDxukAq1FJIi5JNQhzJIGyU5vVRjFRxhq/wU10A8Q5S3CVoUhSMVwihxqYf2tkKMH3gIb9UIFI4KbH0zcYjzCnC/BahvA9Jmzof9ORq0YfPHfH4IfZSucZ0y1GYRf0yXod4w1YppEfgGnRKCYyGkeKiVgmsIYqNEY86NZDOt3C6UzqCaLIjFPGFoucxWGHRaplLNtp5mUttQl2KG8ENaPnmJIHC7i7SHluBzZErUp5pWUzrJiBbkYwuXOYyXrCCZvFA2QO1M7e/ZTn/rUMIk29BJW43QVhlqiEBZH/ev4B50xpzdUyIllKDRRNtLrO/ua9jX8H7XEvS+GPjUcv8YTorQdJi0h2Pr/8I+UvVW5LTDlsnWX7oW+EfQx2ypxOFjUQ/Xs1avpg3UBcqZyNPm96Pr7M9N1NKrj7t09c29jvrQav3XWd8Pnfoi1GPItxnyox+3eB4YPpLssRnnaPObcx3ybyCuONej5LPYslp47WY6vThc/rul0qv2dxhq01hiMb7DnI5esZmsUhtmS4n8k+0JpYrQKsRkn2PbzkjzRCq/H12DX4i9oFjLGsTd7/iIjSPWY/O/HvtJrslP+ldTWmHzj49T1LWY7/PJ3zbR3ISeQHN0Lqxk5PFalNB/311ezCFsFPs0RLSZVt6ihP777vxVCBshh805mqZHbf5xf99AfSRGm5ixIkCLXYRMs1uEYgyibWlEGf8wHWXaBw+JdVM2k/sjgs5heiHTdsnzYUFPYLqL6YlMFzE9ienTuqBvsi8lMp3H9ASmb2G6JyToP7bX20zfavMLCnqKXT/T32daYfpP7Po2Clq262N6KtNyQNAttj6YbrXraxL0Zls+pr9luptp+xTdXqa9NPYNWpfgegP7YjXNcbbXWywVwFeGnk5eUVbBUT2URCsRUoxO6LdC+kpSGfQ1cm+knCFebwgOyG8jWcAmCBewPSXXUumM8qnEvzqJ2zxHX03PifY0LUleV6/SN+rhTbqstfi0SHxpLXVx/uMp+Sc8L+KLlibHd3F8V0p83gtsl4qgfdHQ6XTnFez1uzzqyVuudm6h6BOWixHPr9+YkH4b0FkJ9FMpdCfQ2Qn04yn0n6fQXSn0T1LoJ1LoJ1PoNzOT6b9PoV08RvF6+ZiEeLEfXWLpPuyUouK5zj6sAuzPTXtfsb9M3tfD7o73PmsCuj+8qcYUGyaIXxXVjBX1D2o+E/eRRogS1sTLValR0w3VNWvV4YgVceJFnGAneYGz2qgtCres4f19DdjgymGyKPCdBxaINog7Efvj5+8MWqOLr+zEtPJXovhZFD+LY/Dcj5d14E3YX2nklUM0nxhO/HIYBc1p4lfwmt2OrQGM8Ho4MaebPL9FayY6T0jzbavDZxnPy/H9cYR2V/aO2Uvj3kfnmfCzBPLW054h7g8EH1xFx2NFe2z5bXltOW25bHlsOUR9rY4cdv12vXY9yEelFZtB83dcjiUkfTwOV/KYK5qSbw3NQDqt6BNTaiF3Ypw4AxDPUUNyJtIqtUvUa9dn87f52Xzs8mBXyrxQaF7UMSg/fGbIXvjIeNAKH6F/7yy/f5YgqsFc3GwyFZpPC9VrjkEsDzcn0St8ZhjJGvCGdoLbarSiIOwyK0j8llk6dbw7YgSwD7yq4XP6Was3LNVwFLZM1YmEerEu5I+8kSfyQ15QvhV5IR8sj2WkGtW0DL9KfJYYAT4CvTRZRtShQF+aX9cSImotQXnDOkXWWIyqiXywPJbBfJgH04XfXRwORYKaqcnCRchVeKolbNxp++XFQTUalZWAZmBrW+UKLeozAhE7i7xIjWqcyW0YaisXTIyPF5FVU84X6bWtES2VGXzq8FRPUI6i+/LJZpOhqX65EVTpFznqQqoOfsgvN4OwwNAXjrRCoEdNw6KIgAmSxhnWcb7mepTnWrnj+a/J19+qqyEQUTW1loAp+zUnJ/hYOc7PzhfQA2ZADQY2a0k56rQm+X8jYkL+q+ZM1VOCfEkMh+tzBH6RoAojSNOxqWgv96+TfcFw1DI0wSc1PSkV0sMhPSBD1wajgUaIc7igLejaJjqI939zg6nWB7UkcZIYJue7U6pbWVuLZ6TrKhWRbvlN2dBgMOkBHSqsG6atFPmG90NaRSTkS6vSpP65qp0FDNOCFvgD0bjqQmpkBLsd0R6u1b/X6tcoqFE1RHeAphIYifJ+rUG1guZIqovXP0J50YCUWKzXNKhj0o77+ICvM8FPhBsS9IY2dCfy5Z634xscen25JG2B3zT4lZWVSwsWlEt3wPEs+M2EXwH8pmOeLZBnGiCWwWt/eN3uLnG+HIrQyrsMeQDeQdcRoPyC6RIUgZU/HOMPggIgplOaJIUjQrcoE9r0VChfXi72K2XAaAHkKZcc+yfbx7wbNlg6eIdGXfNLgjZQZQEfX2LasCFiGnPnAGpqfQBpX9BAVUh2egMs4+IRGzaYTYFoIh01/Un5IyomSw7t82u+ICD2lz8/df3d/YhYdx9k3M/YxbidMcJYx7iWsZpxIWORjZbAfKZlximMeYyTGScwjmHMZsxivLxN4AXG84yfMg4w/p7xNONvGU8x/hvjccb3GfsZ32XsYXyHsZvxTcaDjK8xHmB8mXE/4z7GvYx7GLsYH2NsZ9zJuJ1xC2OEsY5xLaPCWMQoM2bbetnK7WM8wNjO2MS4kFFmvLyF9cZ4kLGLcTtjC2OEsY6xhHEGo8w4gfH8w9wPjAcYtzOuZcxnzGY8vZn7g7GdcS1jyeZk+5OZlhgHWlkfjAcYz9+aHvP3in1uEeMcxgjjHsZuxqynBWYz/vYFTmdaekZgPuNjnN7F+DKjfM89tNV/uCGomlsRwRmjfvWwPhN950xYzsIEY2ozI6qhhsDnkG+y9Cg5G8zra1KpTLQpbJhwENBN4hkMgz8HbA4HyCkVFhZKZVowGIhEA1HwYzMwgj8zEhNQLli6hTflS3fdD3yBieOn04izfFWVs5H1BQPz5kUCOrq7MptWcWFZRnKgPHfiPKxCA1tDYSsqw/pKi0ZgCqX5iPk0aroG3lOoAO9YHFbtTGnePFwn2CdCfFHrTtQLbI6hEjFdyVA/rmAlSdOtEOkqbMewvGHQlmY0QPUUdxenaC0Qq8s/WPwDEXG/2QQ1rZtnl4tY9cGAb57DJ2KETZhJNT9HwRajGcR1MtjLBee6rZgo4/q0p06/aqr/w97TgLdVXXeeLNuyLNnyX2zZjq2QEAzFQXFECH9tHNuJTRJHyEocEof42XqxRGRJPD8lTqBtSBmwQkcSCKMrPymwjXZsSwOlAVqm0ayjhVE15W/Ahss6BnTtXMratPs99+/pvSfJCd/WrftG9N3cd86999x7zj333HPez7VvkoYwRqcgqsRxZzpn7vrGPV40KLg/FyAs6smRazBoSqrXiX0Zr4mPY4WV6evEs/1PnkMSypp0zznclcRBxuJUqD2bcnISeAH7DAjaXsiHa3ckiYLGwrFkku51l/H5/jivt5so/3YNNg6uHdwwPIj7H87n0q4VuX0R4WVdLKf7Lylfjvnu5QEfL1/B1hCINQR0DdH1Q9+LiSdlfVxa5JJLEul4HPV7u/b/773AYv98eb8O/ec7g18/eOb83VjgZ65xg+EnneHP2H6/4Wc7w59o6/tIAQrMafR/WgOk3O9M/5k0QMr9bGf4y2nAf/V3Ov7Jrx5/RshYdsYsc77N8Jnym+PbipFMjwf23bD/Mzf+1k033/Lbn731ts/9zu0HDh66487Dd/3u3Z//vS/cc+999x/54gMPPvT7f/CHD3/py3/0yB//yZ8e/cqxRx/76uNfO/7Ek099/RtP/1nmz5/55om/+NZfPvvt7zz3/F+98N3s905+/8WXXn7l1b9+7fU3/uZv35z5wVt/98O/f/sf3nn3vR/9449/8k+zP33/Zx/8889/ceqXv/qXf/23f/8PkGwl9tKyckeFs9Llrqr21NTW1TfMa2zyNre0zm9r9y04a+Gisxef03HueR87v3PJBf6lXcsCFy6/aMXFl1x62eUf/8RKeQwDqh0T0dg1O+OTiWTqWnVKS+/aPb1n79aRbVdvHy1eft31n/zUp/+3+f8/L//uVT29favX9A9csXbd+sENwStDQ+GNm4Y3X7WFyb94+W+E/Nf1bA8PrO8DzAc3ru8LDfSwdYHw+g2DfeHu0FUC7glfRT5A1Mt7Nqxb1x3uo9fdwrO+8XbJ9F7vZYt5XMbxR17jcc5lPN6z4A9cxOMnC35kHo8vLfhHanm8aMFHa1j+657e0ywv2L7kfPocdjv58p/4mJguv5T6/+iEdxI/V5kCHd4ZS0xEkpMYR6ixRCwiR3yLfVpyTJ5ICr8umdainTuTqiIbYHkHxiCyDvss5T5DeTy5S95J4gJF1ZKdiE7yOKBzPBpLyLk4wafDib2YlN2dexU5LifYfaMo+pw4DOZ4UjhOyyawY803psY0OUbu/CuJCYof36vQZxiCqKiBMRIdWnqKJJQDjm1qd0x/ADO1W0EvPtq5I5agdDAASxB4F8Zde9NKXAxY4NNqeiIt79FhxqdP51PHK2raBGO4Rhta6GEmT8o5OIGDpTUt9SaTEYzDDLAyjTUTOozyiqRVecpKHylhpCTn8aFgDCTHd8kRdosvhx9PU5yAUVliZEwJn6qwWM9MZzyJKuYTs2/Ex5OTYzHZOh6cHxrjCHgsGY/twmoCllWMeLWcoqQwDEGJK1NK55gq743FYzJ94JNIqruVCQQ6E3vwmr8tbMSPJXdO5u4L6njxeoUmE1KdQhdiKuUetQlzGnerk4ZiAcfT0xhiJtPqhB6fM3xsPKopGLYpsYQRL6fJzU/sdYeqJMajOXoczqPH8ShwOWJoN6bE2eD5CDuJPgMYYTDDO82wvt73mNe7KLeuY4FP7DXXuwa1lVQRcExVTOWovbGxMUWXcw6fMMHIUGyvkoNlzoAOs3Wb0J+TpjWjGOg6J0qhqTJ7Y5xPtcBPoaGTUXlEgJ3DT6bisR0xfntaxxN7YzA3Ak9yTFHQJ4T/EyOhEyzH9RIxboMqmfC+Inj9vsNdbF/pG9zI3kOwwH4L7NNh9mJ9E4cH161i38/o5WzjtXN4S38/f8FEwOw7iFOHGdzTP8TeOzpsrv+spfzoYXP7u/XyMPv+6LB5PKnD5vGPHjaPP6jDbMNfedg8/g4dZvSadJj179DhKxg/dwp4C+NHh9n4MzrMxntUh9ew99DuNI/3gAXex+HVIc6fDrPxbtZh/l6JDrP+V3C4t4/x79Nh1t6hw6z9qTsEzNq/c4eZ/1c5PBBm5c9yeHBDiPFnge/W4UHGD4eDYcZPVNAfYvQ26zAr79dhNj6/Dm9g86PDjJ9ThwTMvtR5R4fZNzdZHWau4HEd5vOhw0wfD+gwe0Finw4zfqI6zOSzWYeZvFfqMNMPvw4z+TTpMJtvhw4zv3X2oIA3Mf3i8NAmxs+LB83zlT1o1q/nD5r16VkLnOHwRj7e4xxes4rP50Gx3hi/Dwt4C5PfEUv9Axb4loNifbL5mOZw/1o2vqgo38LmN2KBN1v677fAKzgcDDH5+3X5rGX6zuEt3UxeHg6v5foJlvLZA+byVzkcDm8wyVfw9+wBM3z8gFmez1vk63I1u8o9y+0uR6e9xO7yeBzzHRt6gtDdE+Tv2wj/YlD3O0JDvUNvRJ/uP9/97sBDb65xvX7P1N10zi8ZCa8eGrn4wpGhhDwxoI0EVXqTfWoN+mSR7UuXLgks8W9fpcq4w4+sQp9HjSlTI9PLAyMhJa6Qx82oBbxtcGB5YEkqMib2CdNNhqwEmXsk8u1R0btS5D3bVw3ls3jddG+B+llJp03+nDZdI0QPLbQ7sjnYWG/lvYXHQGMuQ5m1b8lCm9CJFqBlxMx8T4LjWOfAvXPznTWUv3NvYb4JrUJ8H59jnI6TEqy4TyLvlM7Zf9BQHr2vcP+EVqH+V9xXvH8/tjmO5Qfm6J+8n5k1lM/idbExCJq2QnKYYxyj2Gbl/RJ5V7boOOj8G8qjlrqERkF9uv/DfcUrOe3gDJSDs6ssxa7L2HV1GVRHyqEa4equyhR5j2FlLcDnMC06ItH3Gsj1K5g8BKZtXVCqVZvxpTYoPeEwtZXKS6B8f8moDU2EVGaDMtXmJ/SO1gH8EtM+Tp9c99QDxAUdpJ+Hi7hN7Tg9Ot4jWO89TFlOj1yTvyb1ddFWc+bjTrhN7SSHHRwh+2hJ0Ob3tpeCO7AB3NI6KEvhHHehruLkS3YJ7Li9e1tKoALLbP5cWSEcfYe9CeAKTP1fxH4dNnAE1ptwrN0VYOP9rOTtZrDc4QW4jbTzOMDzgSq5fjglOV7UJPuJ6yVjuXdxGTRIaak8VTZa6rcHCZ19lYxOqg2gsx3tvej/A79kxHm7KmFBZJm0ILBUWiCdJ9XOeLJVGVeqMsjHU8HoeM7CYWPa/ACTMbk+gKmXw+T6dUz+B8QcOvNxkTJzO4ILl5toi3k9nY76FuEejWmW9k+ONW+24OwUB4FWC55dfwXTGw+IOWnNx1noeb02KJdaqEwy+nri42t2QrNWAc0RBzQjP82Ib+6al2H4SsRjHsbyAJaH5mW8SypgfiQC8wPjMF+6GozynuHznzkXoPU8nMcHxXg8JhzV12NMX+kaQPzLmI4+KHS+zISTGhzQEKmAhjDmaAcaumoylAeNzBWWN6Gdegb5qrBBRajUz2RegTJ3QHWoMm8O6Dx12fxF8Ub5CBy3ATrM15Owg5LTRur7ddg=
*/