//  Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_EMPIRICAL_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP
#define BOOST_MATH_DISTRIBUTIONS_EMPIRICAL_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace boost { namespace math{

template<class RandomAccessContainer>
class empirical_cumulative_distribution_function {
    using Real = typename RandomAccessContainer::value_type;
public:
    empirical_cumulative_distribution_function(RandomAccessContainer && v, bool sorted = false)
    {
        if (v.size() == 0) {
            throw std::domain_error("At least one sample is required to compute an empirical CDF.");
        }
        m_v = std::move(v);
        if (!sorted) {
            std::sort(m_v.begin(), m_v.end());
        }
    }

    auto operator()(Real x) const {
       if constexpr (std::is_integral_v<Real>)
       {
         if (x < m_v[0]) {
           return double(0);
         }
         if (x >= m_v[m_v.size()-1]) {
           return double(1);
         }
         auto it = std::upper_bound(m_v.begin(), m_v.end(), x);
         return static_cast<double>(std::distance(m_v.begin(), it))/static_cast<double>(m_v.size());
       }
       else
       {
         if (x < m_v[0]) {
           return Real(0);
         }
         if (x >= m_v[m_v.size()-1]) {
           return Real(1);
         }
         auto it = std::upper_bound(m_v.begin(), m_v.end(), x);
         return static_cast<Real>(std::distance(m_v.begin(), it))/static_cast<Real>(m_v.size());
      }
    }

    RandomAccessContainer&& return_data() {
        return std::move(m_v);
    }

private:
    RandomAccessContainer m_v;
};

}}
#endif

/* empirical_cumulative_distribution_function.hpp
QC72Kba0F/TvxKASm6aAQQ5JNEwEkCcRUvSAvgx0pUIlKZ5kH5PgbTq3TlCFTke/BLumqmR6Shmf4KmLK+EiYCPL3vVPg3GFgBIBgygk6UoFI5GkG758BXBOfdwkcNf4kjRg6H8m5mXDyIBCUcC3siTQbQUh/ZecGXScLwnrviX8leoltkNi0VDLVVbqaaRRy02+4ouU8TzxYCOhH64x8UzG4kRAhc9AjWb1hCMBuhV6iwlHAa9R2OjKO6E3QoaGIU2kTQ0dGw/JnkZvOARm6f9XENegFYkpReQFJpwnZVhE3CiRa2hUqFW1LryB+KMAh+av/Jb48p1KhoMy+IxCRBLYM0WCrZrQnsKxE2srkOhrg9kF2bg4pUtKPjYPlRJEqfBRzuyW1LIXf5SmtlDjGIVH4tduQnlEYiwYKJL0UkF2CFiFDr6KHplIyznvVfJ7MoFxEFLTJzFjLgA2rKlBLimzxT8Ysa/eaYVYlEKM0PcQsEr0fSG+oVgzTOGjcvACvnbMnB18eQHNyrHWAR3P3EjfW79h/e0XtMAAghEsFB1gckuOVLy1+Y8dV4jg+w2wI/NuanpmwSLADEl0z2vymZ7Djniel4QTu3sa0hkOrJ8/fxJPLB3wpOA9jymwZ4frmHTdF1lwE7r+uRprrkDbBNDvruZLy9VmedViay8LYoQm0t2EBbB6qGsuA8bosJsh/HHfdfh4JvYDxQYingXB5RScNWNvbqZMa8gIhlTN3BpzTeiXsIREVwrCMVGGDf1TdU2uBY5IIkeo0kQHFevplwgjCEdC/YH2pwjCFKKCEYG9owq8gGZlROHjdBnfqbZ3+cnvu0Nvq6PWl/mEKbSBgWUfUoMhEx/j68xIpQ+ErzudwahweqlqNOtyF5NvqvbQe2xW3e58PAmSNsLszBTsPC1f/A8AbtGY6sRDOEwQpzCKVgjT3hKt1vqJsAezZ+NFiHVehL95/UykKYxL5s15NDCpM1rHWcB21niqQeDSpQjfEUI0x5Sz5BeCeslLwihJS5XYq6PTCaOgnepgvlJg6Tt6M3VrNlSENpE5hvlTT9AshtMzuuCm/jttVA29dGlqJFnCWyBgd6geos+NNsKjXnLWEjyFaOPjbNU2WCwPgnoAnv4sRiVQQyOY5izrXwCrWyQwhaDGFyDEVjmTjYYX8HWGi9bZTIIHsBrOJMFQsqcMC4lLwofqAJdoL12l6gwfOA3RiDFvmIkmcKk5ZOYK3QxJ6DUwrD0ebWBLQsU90cFk9ttd0Jdzx7dlh6OotjFnJGsr6RFf2mHnMPSlaVrve96JVwB104ANCJ0MSVxMZ1jPWrIZ1UNMzmAGyMyHFYGxT5CKQ45CiD//IvD4M2p5FUKN0/sl8eU06ZFTqy9y1FhN/hjNC5yagUjHMrY+/gD0or4Gd7L8X8MhL6yHsmhrMktogGnWdavWShSqFg3/ctZOFoukP0Ggm62U5XqYEWEKW0JKa+RbQaq8As1reSKo+rKpL4WF6xPkdeEF3WvTuhbC6lNZ4f1EcvxV78rS4v1qYa3KVZL79GaHrZbAl8/Fx7af9O5kDiez8/HN5GRGR9vJYcBNPY3x09PuDJg/KupXUbsATaGOTT1ZiErYa85s4dNC6HyhMgOKHo21K+wgBakAZx2JMOIX/h7c9twOIM1KJ51gUvvZym4VtPyAzB5VRkIzLAlapg/B+Cpq9wRu5KCVM4Ky/CWcF927g8G+oTUQq095QMjTvKlHWEUfnRKssn3/Lt2QLQl+SZlHTFkmcyyCqmqoTysauzcy2VwwsuRgBBstmUqfvqlGJkKSMCMlFsWsgy2XQbClnY+Ihw3f9IOFhCIm7LjhB7BLCltPH/7E68Q5XLxKm6sEVjZQ6hfq/IU4XbyVI8ZfLV64DcdTABR3LUsQONhbDXibGVs10Q0lz4uAyXaWAf15K5IB+ULKroZMx4HvcixmOMiI1naL4QQBFi+d/EBHAgI4TJsohe4BKvhr+ybKdRsBFbxrTA8qLCkEtniqQCBTyAmc8zi36uYBLpyk9EY/QL7ApwOKy+AnKPc0zPdjaYOh25O9+EFpw/Fp+6bnivjWtbACdemGU8ODtYS/Ah1EJPZNT09F25YHBgy9T90sKV8RGwDOhcwU7irrRVsJba66+JKbHvx04KnPY2oJHQCRuk7kwmvfUoo1J6QFMKc7LuIVvEYAODY9zxHI879ZlQoyAvJVmCtiVBT01OCkp7+wIxOKe4+CAoO2TDZlGr+D7KoXFw28vFXT099pHtGw7AVUN1EtXV8QTywxZFZBUbK5QRt9E7riUyA9YUQMv7+fAnDww+LZHKJ7zdbKARyInrj3qgUAiFM+SC8dFLqYTQHm63k6IURPxqell2Iv6zmnVu751ttw1xPeylynxhPOj45XbO8Rfel8TOwLo7HYew3O1p+AHiE1xb70vhPrLwPIrY/P6QzdFejTyuEH4eUwpITxBiYf20rZDF0DOSTEuOEH+MZIaLpNezIQmniJyjeSPLElJgR5MECFekiSA3xCmvzQ6YeGmxjKx7teVnjF9zk489mhamodic9jdCdho3N0hj3JU3xOsqMd12fif8GZxw1YrHj283Cuq9fxyGwbY2qxFSk2RMDet8Cv+u29E9TUfRu7UDrscx7/ci6ucIXIxC64MN8/Cej28Dixmw0iopCDFyOfaGS1uEe3tLlEt9ShjEpbF4ZIEQ87ytxyYsI+DUCGm8E8BcE/xJqGJiPiVc6DklJagJ69ArVIYBZzrgBfXVRQ6URV3QUukBV6YOKCZzPoQ5OEke/TSjd3PdVPemz7L3fElL6jKPu+q1YYvHjE1D53GT8jaNFlb8Gtpu0aSgexsynYBFLWOgfj0dsK+yvie39DQYqhlZLZ+bN+nmNACozBSwsXUF5D4KglX6VGftjn5PMdrxollv116STrpiPU+WPwuclP2a2B5/73tcT/fnM5jubA0V9kCzB6UCMwaL6K/+Z5wKKjikmsNlJL/qAgm+nPPFcxH0gPP8UmYksH0eVptL97acQk0o1/0JFCHTaiOtVQyjwGypbT3zfMnMSLade2Z6nV9hDb4IYVkEc22NLW91Uw4Ope3OYjjiZNJ9fRUMzCDG7LH7uya7Zzt/iNulA20RaV/QYTinUsJhRtALOXODZ7jEzwmqiwMIEAs6OBSp75/drVwtBG9EiYFBjtuP6p60sWHoMDxntUqsQyOtN/U5agtOVLrCIrFF0HqUnw9/o+iPoSGPDgZTbnUHJcK1txyB79qh3DXCAL9Jjp+bP1XCwkm4Tl4Hu7Y7mWj5AtwS5nf6bfK9a5yvFYcqFlfTwJFfAUbN5JUhD8bKXmgYS4vFHVYf5KgpfncW+XDiulcdpzRm1iFvMuC21tVHiTu7IrveiRbHn+0TCAvT6Poiqi5A3AfJpt9TVLlRYkCUVd76FATmt4GlTs5StgKgyUBHNM2hURN4HHqazaPWRxUFUhP0Q1oiJ+mfuzkrZXYGEiNFTBPTIZPnD3IEjhaQJEsEN+TZ+pUPE9CQgegB8mjQyD6qRRoHXoqI+xHGjP1/ij+QM+9i3dZWC8GSa94L/PigYDTo0Bq9yf4UFNV0V2a8chwIlpXf8NWvBpSwBLKdQLS6FI4TAqudlHi9mt3SrNWFpTyO74w5egiRKmoE/AeinP0AuZ7FDDc919R/tzSEHjU2cGm62Av+FCw8HN4/4ZgiExCinwV8R3kWYyYNrh5A8mwoA03IjycYwTj1QZT/yMhBqK+/TuYcncJAwV5iE0tyYw7jjXOV1ZbVDn0qKuzJbTeZpS25/O0MUWBfa8TpfhqWJoj1IxDkYl9sBOu/PpAjs0V+byLLktlvNSJXbN/llnMyrXhQrqotrsTshFVQV2zYiSDghX75EpexM0g/kpsUIAMqw9SfHXBwOzEm5Xshi5BwcV9bzdiN0LisSHWiwkDnsCzntGTFNVJpJ6KiaTdmTcRkF9bIvLEp21HUhJQ/ON8MuF75J+PsWsQlJwtMc1goa1w7mow8CfMMeQLegh+FWCmh5Da/oix2HDC8m9tC8TdZKQ3MSB2E+csZ5Kgt/oa1dsV7L4IYFx4rhfVw0VqUqX5jYsg6JloRgcXuNLARGhcruLTokoUQCBKhWlW0D0RgEkyqxfxtsR/FzsEL2BH2TLq5NLuMPETugjT7j9gR/5eWTc/2WB4eMPtgMI9HTuf2Ms6HvKP2m/KjQGjjagzxef0OIMKRl263mbB+iBng+8qxjQBRgF6ALADFAL8geGAcZTDhgH/BRgFfyWoZ8tIBXgCMBPIn1me6RHS0ACvp+hH4QGngDWAKy/KGBDL+D9FnINZgYtwCvAaJEbIgE4AZYBlgDTgKm/7I2hEsCZYIZPMBR8PaeAS1/uaIARdffZpzkYxgVQCdAMEIb5iOqioGcDAA/UA26XNUAKAFkA+CKrRwZ+Pxjdk/FbYl0jdnqf25TSO3TNGOSPpIRi/57tsqVY9WiN2bqETnFgeWS+dWZpvQcQKzWWziI/v8IxUnWQErYFivqx1sE9OD0a7KJVhRjCIq0Sdfc/0oUxHKkNeSEE+lOggfvGgkO0Sl9TrNhR62sZJAAfsiX2IDpUNxHj6CM97vW5ezbUpeFzqAagVKZmUynXufzWeILdZQVfEsFK69KwtJidu4gzkR6y7+j5hnn18QYP3CV6pspRkv59HxXkiczE1t26oBQEbE0JmuKISXLVIUkclZU4UAeLvtOqfRNp9h3mBDcWS/Rq1CbU0H8ll7EcjYKlU7r1c7fX3V1wfgmug1n033JO44/pn6hR+kDl5dTkTJaES08HxJCvdt0Ks2wk5psAd0j4Q//oCVJKyKKOKkQcyfvj5qFZo36UaHECRWp2m0oWdRbH7D/JgR66ZceU3eDhmFifwPROE7BOH1h33/PTRfFQF6DG/xhBR1MrXLy8BunxO417ZAdXduKLU7vxXJGEmwyMoSATf1IHNjDM+w/vCnsrMJ+RY4KitAXwxqqMykyL3rphrGWgD8yA7kwmsh0EOkY85YTErB8gNc9vgj25CL6Vx0JcnJBSB2ZlUfpHdzpVAkwE8tvS2IBu1wDg0QHZoA6izmpgzyK6XqIoYbkaW8RakWtBrmpFoboeR7gSytwoEC8NLA4do58jVRZ4qivmCOFVsktIaMu0yBLeoAng4T9on0YRf74xf0sR6GO+Yu91hO0dK2tpxDcwprq4IvJV18+6QbYO1H9bW2SDa4U9iJYrc1q35VhmEO0Q1FhoAbgdcJ+6NuQne/toyCCj3hnhfKOIvC6TRPKivtFM5iqFpTfevmi+ftDgjP51pPkERvseYI+RN9szQZMz3ENBS2uojwk90OTIDUVeTQZ6kDfco6ThiQwlb7gFQcvt//sKp7T4VNMe6LoKzL3qLqa7cLbgWx9WS4ebqyl+Js7sq+kuZBrEVUgBMjuS10py7E7O+wi25sty3evuNBIae/C35Az/6xlvbUPSnVeeC42vj9d7rr3efn/hW/fJnrzHJZMm3b4lBYauw/Rac2VDEr5fAFY2h+lofMcSllyqMvqa7qqn9qHvuoNzc/PrcuaFjs7vcyz8G+kjta9BIOceUAbACwCOAFUA7LYizTcPFAHwRzLAF4AbkA0YBHAT4N/vVyADoAlQAQDJWIoppr5R/po3qfN4fE28nLuZ2vfq8PN44K6xQb6C3vLzxqlfEEmB1j9+fXHuagOmqHMsqcHca/dJUvSRnBLTkkxRO8Wk1uYhhm9IhEmrP0ndGn6GgDNX4l7x6vNMuUaK7FAUeSsL8LY95h5o3EhBJyhUnMdXi7cRED69SXApHPqD/fXz8wPEDAgA/AvkF+gvsF/gvyB+Qf6C+gX9C+YX7C+4X/C/EH4h/kL6hfwL5RfqL7Rf6L8wfmH+wvqF/QvnF+4vvF/4vwh+Ef4i+kX8i+QX6S+yX+S/KH5R/qL6Rf2L5hftL7pf9L8YfjH+YvrF/IvlF+svtl/svzh+cf7i+sX9i+cX7y++X/y/BH4J/hL6JfxL5JfoL7Ff4r8kfkn+kvol/Uvml+wvuV/yvxR+Kf5S+qX8S+WX6i+1X+q/NH5p/tL6pf0AACz/00vnl+4vvV/6vwx+Gf4y+mX8y+SX6S+zX+a/LH5Z/rL6Zf3L5pftL7tf9r8cfjn+cvrl/Mvll+svt1/uvzx+ef7y+uX9y+eX7y+/XwG//rv7nMj69Ccg2mJNs7bV8QVvFmi/xiqPjbiCDP6nSy6xq8IjlfSZNnXs5iULyhYKCfzc/MGFvzKFnZ9yJUzayVOcJ+/WmVZbS868sqx+8dQKV7csFapLprVg6rL9qXa0FfmeNbRrvZ2oxueJgE/lbLETJBp2wCHBMOmIxHUR1pzPsjZ47xkExd42ODknBJ9Ig7R9IDmrPKqYBB+T3fV1DL5c2X5lwzv+rC1lZp3tqmjjHF0IW5eUYaZnQr3XFxGF8AJDfXx0uvsshDkY15GRO8w5FHq5fGx8rdk99W4ukxjY+NL8f0RR4E1jY/3ddd70TWJb6f+wr/fiC4c/FeZ+Y2xK9ptSBtobOyw51EIJdW51MO4kBQEkALTjMp59A7t2F/n9/HEpv8E9kRSW6awIuNijy5P8yTWfL0li0qeVUV+MpVhl8UdhbFWNJajy9g0yPDBiUY33fxYck2NspXAQ3BzFIJd4lYA6fOFGMH5K7QDaDmOlU4NxjKNc2KAwMYQYczVLgROefmB77wYsflVWUjpBj1ktqvDi0ElJnaamRrdhH9zXOrtXHlxfLO0A/ojXfDTTAgHl3r5DHyiUdQGvaE5bi0ZLU3Bil7WohV1cBskhwDqRyJ72pKV9+GKNpRsIatGXHeO+i60dCYCGq5ZEBpriK3d0IC1lM5gmI7SOn4QElLclxrmAH2FfhnBbHLyjtrTvktDL5eqrNHC0HNj/JCXA3qA+Sd3Dl5x9ttjPFgIzr+GXqE3jqsCSVs9pogSZ+yiWk08mx3B5wx5nLvIri8ZJ4rDGAq7KrkWDX5SNdH15Q1t5D5pM+kxHIjmtNh45zLGzqliHO7MyLLFzitMQdmMT9AaWs8LprgCzahY9hmEVDFVL1iZgVZnfEIHOwDspXi1ylAvr0JuAweIGdX72i21a3lg9tQ3yRbCNCv/0wxC5MxqMev7LqKCgflLGjltR1LocChc+96lzXH4HcuL95WYANcfEns12zArgzjC4L8/EvR/TCKxfDIlxgUWB8HccXcsR3OYktIWqktjTcXg7s9NoBso/9odNoiVo3cvcUAmioYUV1mXfR6TaxUFE+byPHE3d5rW5GSJvVbocvhHNyzQ1moe6ib1dh28eHzv6Uu/APZaECJfpU5luVUU8E7SbvMoCyavVbmiWFVvvnmNdq8/FRUex/29YLwoXNpZMbnsx7/vH6FoRP8qC/JHd6SpX91rHVZLauX1rWqpG9BJVYJF1iWmtarvJqyBL+QPbRj4ta1X9z2+ig/Gq0A8+69HZEipDyjEFisO2JThPUTq0hGQiOYZPKgpIKCqaDN6VjZMi9AGq0pBeS6lrzFjf2csaZRjKKRG6pUW27ALZ2rTZtS6qDn6K7KXtJtc4e2JlFCxgvJdtU0FDQYv0QEvTiqaSEk1YQUJPAafLN/0wLD2GmYTOPHge
*/