/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923
#define BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_container.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Emptieness
//==============================================================================

/** Tests if the container is empty. 
    Complexity: constant. */
template<class Type>
typename enable_if<is_container<Type>, bool>::type
is_empty(const Type& object)
{
    return object.begin()==object.end();
}


/** All content of the container is dropped. 
    Complexity: linear. */
template<class Type>
typename enable_if<is_container<Type>, void>::type
clear(Type& object)
{
    object.erase(object.begin(), object.end());
}

//==============================================================================
//= Size
//==============================================================================

template<class Type> 
typename enable_if<mpl::and_< is_container<Type>
                            , mpl::not_<is_icl_container<Type> > >
                  , std::size_t>::type
iterative_size(const Type& object)
{ 
    return object.size(); 
}

//==============================================================================
//= Swap
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, void>::type
swap(Type& left, Type& right)
{
    left.swap(right);
}

//==============================================================================
//= Iteration
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, typename Type::iterator>::type
cyclic_prior(Type& object, typename Type::iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }

template<class Type>
typename enable_if<is_container<Type>, typename Type::const_iterator>::type
cyclic_prior(const Type& object, typename Type::const_iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }



}} // namespace boost icl

#endif



/* container.hpp
p+R2Apxh+zbhIvCvGBV0pgxK+At/Bl3jdsIyROS9sWgHMdithS1iwHN0EIuJzfXNm+d964imPREUga+PZoM+6Rk/e8aXEj/Syi8ZLwVTvpGXYhjSWlZd0WAr50FVx0LwF77HMd2LqezRBsqLVs8CH4f23IZrIN3Vt9oAWVvhERGSWDT6k/gFWfpeSJtWYY2S/elr8l5nnaUBouUh9N74h/OpV+FB5it+mAkgtjsSTH5iRhi3zDXBmgtsUKGXuSL0GjxlYOg+YT34hpE68MIGCNzPNfGXuqYUIyq06OEq+7fc9mO5l7BDxfqDTZaatnwZjpFk557SATlBqJfswx6+M72+U/X9v4gwwcd2Vfz+Az66ldqHB4fLgasFFvvQdoVCQaglxYftdNl/HvtqonElseGhEDD34MFeU+/r1At+a+DVNh+/uzbDwT+TpUJdCuChONVlAR28kwrDRGnPXHNVtduG2v9XnRXwwuStV4FvXBgSaDoFfX8MgpJ2ayXm1F12PQVqDzwqwCpNZqS0fkEZITSnKTGtvxm3Y/0PS3NefoGMxC3OJq5+wGH/i0Wk8lb4eUfD5x93NsDuke/1khF3fa+w1qiwHXeCt7YNtbk9sObnK2A1rf/CQ10zCb27l/hrsxo8b2br25OK5haGxX0v+T3arFyHZ6QDcKOXm+boXrUtftHyK2BW4ppHGj6hSV72+OhiR+3CgnceNVBU9bFYwWfry3GYT93P0zL5DoBPrsRRtQ9JvDaiyaLGB9N/gCiacyWvdSDW2J8xZBqSgWSBspVjyGW3LvloEdG8c731O5/1pgCPeBTz/TEAP/FtFb4OVNczR/SjsDPj7z3CS5qWlBkJDzvQEdciD63Tm5z/bMxKfLWLkgNb7cHXa1S03rtyLq8acsAwws+gnhs+KFQ8sBc7EpIdulwUFH2ZICjNBC7/GgZ1WIBSB5K/yHsZPICOzeiivKFxKW5AgsEYhsAqyu6N4JknPQpnPEdgq7NxU7GbbmaOFjHt9y2I7GwuWdkIMHS417y3ra08iTAfi0L8PNc9XpAbDKJ6QzMQtVsJ5dDEOxMW4BgqV9zA3YEVNgj4IqC+GT/OXrm4obW8U03wf73w//33mS/iBQNlG1EA4Dxk5bZPofRLlEO8P3q/GhgEAdbhRq6HCv4JZt+uc+yoRZNaa+bmeivD7YIKx8/hP1gKFConCHe7miv+kqh3SBTdi/Rs5P69zDFzyR/eCVYbmIQbtMmPFbTQmJfM/KHAhUg5fWqnccUR5/XFOtZthOAoF2J4G0n4Om2ZyZzX9Y933Zmq94zbATWCXQTrO2SM8ifDXQdFTh9qyUDUY2RjQTOxkyGXR5Ci8Ui8bNtXGAeeIoyAwOYL1r4LXIqGELoGB9TNHmWs2OdBUQhuLdk1yJvJtCyl5sEnVw+RFrOHX2zuIaFv/qFLAJr6e35g1l/fwPvcEL6UfJ/sOsTBqV0kSnirSm2UUwgu5pKdALF2CD99w3gA+Knt8hg+i4CIqMJlNTAsTETCthjwx5N0oNmdxOaLdZ4BI/ZfIBI0AmxFL8CAqFQUX6pr9po7/3/RZk042HIWdiDYFr/y1iLg49hDYPeY5fw+Lwrge4OuhW/u/wbv65WdiN/qdNj5BM7aJvUiZRFmu7Aat6DG9wlDF0n39TtYyml1uN4NOpzzeXWw3hU6nKG/ZD4xyKDAF4oTVpzLkR+Mr+VSrXO1fWLWfr/c4OjeaV/8eFxjzOiq6z9FtJzUgPTQxDOri39iRxLmBefRbqTcYw9mN1sBx3H4xn3HQ8lK5s/yjLk3WWNYNYVfnCpB/GyoJuH2rBV19EYra9qabHYPhcnbTeTtMZu6olL2H7krl7KZskJngD35JvgHSYcVUyQnH9qG1EMXuM09wRroBqt0s3zz8QMf8t5owK//8wHHilOutjxVjglcYhLprl737X9LlCfGelCQsT0EskHPyRp2UnIP3gDEnLyyQTWqsomntKnhKpa5Lx5kLrzcVM951tY84W5ai428a7c0wWyj2GDFvZ6BatO+HDme94AgCoEKDGmtNzmqQRQz1rwPVVUWoJ65f/59yNtvHzNO87ZBATpD9Q9gihRdC/ACRJXHLEryyIVi8UqttKpvE4GML59X3Fa/4KFxueyrcAIrz6BjUhpxzKmHOY9+G4iI5hfNMiln4ITQM9YAY6ILsXv4ju7+YZjSscMNd1p97UJ3uPmIAf4BiIotZNeZM+iZ5upwAwaSRvTcSoJgacTZdd8KXvvm7KAK7DosM5tGdnPbzxHaiGkKHLeBMaC4jhgt2tarK2qqtkhNcBuTDNuZM8C1sc8rxCcEyW6Zeq3w7OQK7JI6FV5uTt4dFsXa6xW3eObRPtfXWte1UnqlAxEVe1rwhaJGh0SyYLdNSy7OBmeMd+V5T9DO74YwSf3QPI/hdbMXc2kVvQxJFS/dH8FGeS+7NdnCEBiPNyWq0Q2i1mRPl8BqP2fi1/xl+ZJHlZ9EiOnRh9uDrCD2HwdmlV7zgSgPQW+FFI4NAyAyLIPcuzTOXLexttpoYXFeBuKlxnxtwCOFSYbyCnIyz/pR2BWjk3O0/zzxopLBiy2WzO1urf2HubUkwVdqKJ7DEsfWG5UvUyyVeVzf1P+8xjD1BZ5gBto7mA3YTCCfi+ThGc8jnkC/v5ePZH77jHRWDBGQg7kjnnc8aJclcFkby7fGbne5k44mxIUYjZCnqBGadFE4j/9pblz14GRJkN2DLlwqXoiSgSBN2KeUzu6DQNVvZiJSSiJLPjWWsNZu/Cbtcy715Ln0OsjniVmZs/hkIAUKe64KtZccp3EdcpMtMup5aSuUyvWjesZxz+TCuOSVpFSLDJnuHZ6sF7Tf/UWU0UL7aDOY4EDRp0g8+MDkLQhtVkzXQAFK3yMQFHYr4ZP3LagYPtaK52QehZcUlwcg4rkOUWDYM1z/SbxM2TZUEtaJOnCQ0gSWtyKLsZSZ0FpESGpwJLVZ9cJE/NzwKIRdupfJ2H2FWOaHePfoV2ezTausNhwtzSfd5CcIKFHtkFhD8a4s9c0Wosi/XHbmX3UhAr43FOAWf/EOky182EQuRL/BEHSuTflckARorDNFRZKcs7D3pP3v6V/knBPjXGNSRjTa3UPwN0cetJY2R4dBc48LIpUr/DVwpxUFo7qe2lGdITXATgPG3PINBILY8arLi/hZ8Bx+YsLlYg0pfbRKQE9PW4OeHsxvoGfhNZjX4SMjC9zQ08gzwP5Vf4fRk+9A89noZ+E19dNoBQSpHf4C+FYb4e/Qj3ln/s9bkFS/+I9ghsRrz5GTWrFG+u3pLzbkxKnTqjj9VnqUovUlrPTcLelrwIvEg9qcUk3lKikhsvPtP7him5Kd1ueMwrzXzgoYnzN8MuH2GEdRyo9JiOYf7hBNer1WFJ3aidn0X+l3SPkXyblqtdQ8K2LlLydD/LFeyS8oJJRXcVsR3wQxJ1HID9MqkORCpCR82E9yc5Y58Bpa0V78TeJARhbfDr9YZ/iKRe1G/g4611aSx4/JI1T2DfzcaPkG6nz4Onjkn3AklLzuEpjr0mQwo7O3JwCuiq/H2HyTDdiFByliormGp4qPc5c55mvqhUX8/NO0N769qPtfZc+S79wi8tt0tWz8H78CsyK3gab7ykWnkDXwre8DfpeRgNJcxhtLFB/ilAKakIJKMKkNv6SejBe/sByLXy9PXzn0wt+zn/Cnf5/8UnKbv4SeGz+vTzjOUF+z6QFbCLyEiwcJacU/Qy6M0t+cz3l6Xb5sOlQ86XTfQpKpcFmSqa640qlUXguk3/PO5WfeHU8H6OcLc7OLpIvnzuMeJDodzwfLqx/jhmKxaLGPWCeeofVkhyHIbVTZEZWn7jVg20vziB/JBQgNrI1ol7oGZvpqxTMRM120gDyESZAWn9b768azXZuemhyoHJ8ER2vQGTW4DztObCxosQIe3oV7chfaVdNXClvccyvxTfaCvDN2/9zdiI1qOoOaKaRdDSMwFed2k367VFmZbV5iTFxGYE8hOVqCc+l27LbkTR324g8G6MJd7QjLuDBBVLUx7bYpWdYtgTv3qmXXDDeHZdU7gxMDGgH2XV0TAqVvv9Lob7aU1beoE6tSg+ht3EP4mRFC5tCF2Hs2B6qAqwuhwIGv75YtXOcivDLxHxBehFigoElVG1R/R418NMwuRz6qIHwI+R7ejeDWe/rEUzJZKWpvBsBKF/J720lh3Ky2w1DUnuIP+6Xp6X5Lja5xh/mOeq8SDI9fVL/oAnsGBxyltiaaZhnomB17BWcjtq0bxqSe5uBFfJc3D3MmcwYorIg9MTzHVc2qgenUn3FP6ut4IptjDK883ivxrsYmOepICq/vArQq7BTo0fmO/95w1ZFU+h1lTyUOPjgW7HaoRpvkaKekYkdTarMaE+rw6e356emRW6JtWC639nyX6OuemLwYpPWUuDsv0+3KL9UKW459mvhYf4z5nhMXng+xgbku7Fx2h5KuHXa7MZViiCEP/4Rj5abDBkv+48FuUcbGg4O0HX6k//rpVsCbKIlgOlrOs3v/+VGvAyg9m8Ws8o//XZg9hXXjjX1/TvN7+gXOfFvAkOX7f1c4dPnAeisvN9/+O0GAY+ICx9DvUyiMYcugjCExPCjiYhxnEEAyfWCEBJK8ENXFKAdJ7y8jNCQv51yXtdKy6fZpkbltfH3/sK69VfOj9ey2QWIAFBWgb0b+oqBaQgbGOhrMi/ewqvaZ8T4G3tSl43c0zXV6OfWr7X7R9LptREPJyhJ4ohJXJSXPezONslM9lB6/n9Y9fk96C1BXum2jvxyXtLnRMkdNtbGvU8zuRaOl2n+lMQYOiJKo2bsEpwv3GAqdPWAfKhG/29yUqJT8tf8H/6oF6nbky/uIkR2oxbRG0OGhdPX5ZAw1/u5orvaW5XvZxK844ceNiXDeSPIVtZv/xcow4kYWgTMV/ylmS/Pa5mScNxSyc+Nc8pKrz5jhQxGOGh6/cq6Zns7AJw47WDWmpXRO+mtHb40V6dKO3vRaxx/6BaCRaib4iZc2K6ZOBo82HNi/OOghE8peIZt2R3KhqHOFfMwOa54usldvxpk5HIeo03IH3i+HkWPPyp2JWxJjl68zkledMbVR5zNRm0+IscI3cx7KdpYEz674KBXHlIAz0u4vVRG2V1RT7JTfE3jVOIe6Nn6lcgw85SFZ7dixknfpOEsKXH+lfdcd8rE8DtwXCiK/j2G/2EK0mBhMSZh253YklEoy4B/5D5yaf1t6m5BjO2Yu/kPF+FewyI5lDvdZqr8cftoJLsS08Xui92sfwXOEgW0sZdlHLNvJzD4+dzhLGvQEQneE5z9vYmBFhK4HR8F7IdJ1RUSq8/jUiJnEKv4nUx/Fg6E3GPXkdl2iMTjnTFAV4knDo0fo6KuCXI7aPtNxXZYBWi/Sln9JvCdpPdBjhYtG5260c6RdnDfb2KN2ARG7zZRvgtxw0cOGzRN2XxCHQLAjwlhRRyHYmySX9l8dIKc+A32KDU2IXQVQR/mT+Wr47XiwKtvXo2JQ5o0kE7IhMTUh52CjuQ3AkQP1XVNytNj2hby0tszh8CwYLvMofomk6jeD8OHLrKxOt7TQU+O8i0dCwAhbwU5svmxhIRMB3lNcpF4KLGAgVEgeieORz6Dz6onfHUCOdmE3plfcU+wSE+msYEmCGXWCgpsdVE0lZ6Pw272BKdvYIi3YOyjc4sbazRYIwkgb7CGqkVWqcamRg2puyWsrza8g9GSmJ85BppMHd6RnYzA3+igYdaHeAy/gNB0S8X2yX6rP4RqDcyGclfOcepAeGtFhiP7L4dmVNNlu6v7/UqC/RdF4tJxrGb5kTk0ZnRG5A366bj1Ap5sgs13QntL2kD/sWvd441B9Y3/X8Lpt3RlN0b6qH8Vop4G9SqSMhnG+hVYdpT9zwrQYmv0SP4vNdSPz3OeffIiXLFgVtDWEfbwZPD9JdLp6AUQIq2f9L/VbvwEbOonMht4tvtH0BCwbaIpkB2mvaK5Yro04zjgKZdeNQ2OQrdfsNO5GpIXv1NjJP+igP2fEfNwmLQNn5kJ7aAMUSJalJFwgX1Uu3DbVqnd/siAv3OaHnj/Hcf2Ev8mK3fIGqWekb985z596XMaDnnI8RkmefmoVjnuTdqZPC90apW5PZrinqLozyfNeY/Fn95qsVsxXs0Q6Y8iZwnamKZ967sLLF3iCOYm6M0sL3B49znQu6bNWD3xOBPntc9qvvb76G/qK54zYdozePIJ1ruuvfFm8arxPuS4YiV/ScPFqFVyPBWM9GqGR4OpdDWJVVjGdVWgiGn/EUNiTUk+6cI3AqMg4onkp4Oj1VQxXHbtQ187u/i1hZNc2fA7P8XrHbBEJtG6R1ynm58lCyCRqBe2ng6aGgryvGARukf0FdOa85c85ngj49if42TKVIGZjchU2fZC8jv9QDSnGjP6ZfTvWc3T1qLZfq+ErkrRVCiumE886CvGcve9Le5xnepw/VFepD9XLkw48oddGimP0gCx1AEEri+OQXVCizY0KJ7dXjm2dM7uhFSJRuHhM9S7vPlSUA3cLNzj2e/A7b0G8547ZMWRyxRgyLHJifeCT9AishpgK/36uW33bYuDPfgFQCpHMCWmlJ/mFcpL8p5zSO4HzRf6DDUQVZPsqBJX2nsy+jPI/ADeAyH8VMIWaO+vNzCtCZhBBWQNvhlt4GbOSyngaU2TyIuZAdCwji1HWCzBL9KQFSsI55yjbKpg6SoHqhm9katFeMansz79POcWLltSSb4cSOhsID69iWgkjuVQksaBh9VYQI0qRYNch+RLpeuvXxkm3Osn/h0q56fJsGSU02khiOz/99l+bTr/C4gnp9/EaoN8aTsDN6ERHWbETJhwDlwyTCHhBnIA32pqdw2ybGGrmQopGwLgEUDQJEW8QCtbqQvMpgUbBV53kFFzKTYs2QRQxdD+PgiRcKg7fXasU9mlGw4bXyk0CmymX65x3Iw2fRhrGCoTiNAzUWyMiJTelVqcpiY6zoUZNQOiCXCN0rbB0lVo6yy2dxbgZBUSN3y1J9Hn6LTtNHWhlHAjD+QCQ8wkd+fPJb7CMo2cLp2cL0Rqg39Sn18Xl9K1IRBagZ6Q5i0rPFk7PFqIpSLG1l6eosIBI2Flv0ejZolghL6RnC6fneBklmEKV/+eoeWbh0LEgPYMEUYocFej5bBo9W1R6jpf9Is8pXrSklvx+j552uzobLKwINbIi0sisbBlqZNPYrKrYbLKC5jH7lCvKuNpYbTNXKrPLEsQfJ308wLSxYS0Rf/XqBN+uS/PHFLfHxgVZmMTyndFQHmgrOBG+cwpmA5Jr4arKtaqkK4K4z2YhLTXUyxKJ+CeDq7nitA90JIDXi1r0QtKWKGgHeVi7AdXpMtSR6EWyjkQvQUfykU4FdVgFArjzJJ0nkRpkR32KQuCDGQ0YCdln9LNPKTWMSVEfstWybbrHnC1G0w/62t9gI53VNiOMBd2wgbl41YLvN6D6UuP3RqptWZXKY9hYXIGS6mWx3yXo165K8z42QXlzx5f31ETlzR1fnvTZ+cs7T/98eeJv7p+5Sf0zN9E/c5P7Z25S/8xN75+5af1z9rMp+id8DNTDQVbsAAEun6yK
*/