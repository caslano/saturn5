// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_vector_hpp_
#define boost_numeric_ublas_opencl_vector_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/algorithm.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class storage;

namespace compute = boost::compute;

} // namespace opencl

template <class T>
class vector<T, opencl::storage> : public boost::compute::vector<T>
{
  typedef std::size_t size_type;
public:
  vector() : compute::vector<T>() {}
  vector(size_type size, compute::context context)
    : compute::vector<T>(size, context)
  { device_ = context.get_device();}
  vector(size_type size, T value, compute::command_queue queue)
    : compute::vector<T>(size, value, queue.get_context())
  {
    queue.finish();
    device_ = queue.get_device();
  }

  template <typename A>
  vector(vector<T, A> const &v, compute::command_queue &queue)
    : vector(v.size(), queue.get_context())
  {
    this->from_host(v, queue);
  }
  

  const compute::device device() const { return device_;}
  compute::device device() { return device_;}

  template<class A>
  void from_host(ublas::vector<T, A> const &v, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::copy(v.begin(),
		  v.end(),
		  this->begin(),
		  queue);
    queue.finish();
  }

  template<class A>
  void to_host(ublas::vector<T, A>& v, compute::command_queue& queue) const
  {
    assert(this->device() == queue.get_device());
    compute::copy(this->begin(),
		  this->end(),
		  v.begin(),
		  queue);
    queue.finish();
  }

  void fill(T value, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::fill(this->begin(), this->end(), value, queue);
    queue.finish();
  }

private:
  compute::device device_;
};

}}}

#endif

/* vector.hpp
IS4w+h7IUDfnOlOPQKeCXalcG+boMWaa5lLzlqJUpOHgvx6tyPe/582LgObG+AAN2piFzFd3EoRy7E8Eas9b8cF9mYCVV6cXzpeUIzlhyPAg8mJww7tyPYrSouVMCiRsP7K0VicEtYnEJCIQgzkzPq/3F5lGDp2Qgd7XrUHHH1aTc0IlHCALPLZFp84RgQ3i2ogAjG4OrF0qfKhZJTKEAsWp1OUkJVV76WQRX6jSxRTsvlCGLsRwHLbVgfuQgxwws8q7wy8HzeLxY9VUG/KGC40XO608id2bmfhGScQnke69McMeHBtr550jOE2om9dVkn78qele/DzMqV7wXm92q7wHLM2nVst3u24cLY7sVA/8Ne+jjhJJ/Si4RTTmB3h+v1mIOnIiazanTPva+aNL87emF/3RbmRA7LvC4AcP6VWqc6sfzG47mWEJx+GXFr3bln6apgAZv52Np7Udi0HveKFLaEtg3qdyWaBodYtl82jrFBdnp9Md7W2Qtxgnp7MXzi8Y31sXkmPOCKCPl/o5Ml0FhShEG7+F4CnXrrMEsWRaauWNzqOM9ywlq6ycK3K1atOhvbtjV5ajww0bszJJ0GYO0l1pPML9L7K5IC2od03mqDfUsUWv9lWEWd3RlGfuLFMn87A1j8467u6JvOTq+gF9Ud69d8PtsGwCG9j+maEXIgLFk7AFauRK9MvlPxbiOvEANSEztJ5NLKQJjAIA85iXx7SnVxeycsQkX3+jLP0wEQMEJ16z9Y+qE3oIat1yR4JsSNzMXAcVctIjDZx/cpcsmxvhZrBcXqNSyGuDXmxWGGKrCLu66+HUTHjoYxqTD3MQBc58EDlEOBcfKPkEyE1kvlhBm2dLf2cbCokOgwf82HDZ29AgswQ6gYykIU3pZ0uVAwFSZqEPv+lv+L06aTLPgedZixc9Xt2wgA1UwITWJHK+mfOmHhoGnA/YvJ+HPhlL+gg41llAHy9f1+eJ1zDKXyUHc6WBh9g8fi4naH/jRRucKJW25MiKzkP4UQTftGuDukRTi2jLEMjh1qfDsuZm/Vr0MdBPhXgJfw//5am06RDli3PKOK1bWdRPGfn0mAPbNAOhNe07+VnAUafCzX7/9bXux3ZZzaX0GEGwpnlfceRzEreOr7AVKkUKHX5NXtmTo1wZsI/owWZsVe1UbzlT9WcEf0UyuMev01lWGPK0E5Azixni4+F3G5bsax4V/3xxpXn78SaUpNRDF36UieBmxzwZHSSOWbqUXoPF9+egbp5t3+LGWEGNh3cpx1pMfmSeihdBww0yhTr7/emCpI+8d61THWFJXrVE1O1ZDmwl9f6j38Ij7o1pNEZizrrp1ILmtEbLeOgheq1f7oPdsYSteu8ro9GdA6CFPTjTGQ0Kjwero46thDsUYBO92uf0zrjWd0fWikzqaP0gPYdshG9Sql84EcfD3Xi/XJFEEg9Ko/g1fj7ISNizZI8l3O9v02oauhTsKu+eUmApm0yLLxXVxSPTJjGjPwQ1ogwsGrCzbdQLPIb0DC4Fi8ZplvdrbZ4c23ku80GzK58CC1Qh/tBPt0mAT12yMKJ74uESRGz8GqQtj17iTgfLHu+jckyFUuZG9V1Q9gaLx4bu741ic72RZpiz4eb38z18l/6tZLCS5g/NZumlxiXSdDa2nyYmQsOkzwlzPJjCct9PES1Y+L1LF/NgI2n9SxEMEEGz9HFqJHJwQF4cNCffph6vdE0La92bICGn6cMeJBU+WE58Ma1UkSWDJ9jHbtnpN6+xYC6yfSyPutUx0XVr2LxIE/BnTWwSKv0LSOMd+e137O0nZrtLIMhQKQ2uMqrf8ezdM/2gM5sfJYW6zTG/Gba8CzyE+pqos+NUusy7y3ccF8X3bllFP5+W3WaF5IuB/EdphCB09++yAWgeRuBO+E3vdnOugVI0CJVUuISpGpDhCqQ7AL06D8fNB4WYqih0ubo+T4VbPTcGfVAND/yYDzhwzqPDCPp1Ob5heZjboJjyZs90bubv9WwHLxM9M8S+79Yq21cfuzc4XCgMFOFiMR3FcIrKTba9zQ4sPJLOHL3wo4C7N8nMNubUQfltwQvqZiGjRd/B7c93c3hqzM4+9zgnTOwLd4TKyt0Da2OvFyVIMncNSraBx9NLiKIZN1nTw9rt5MOPq6cSVX3e0s4JQ58M/Uf0rGsp33svU9F0/pnR7XobjRhwf1EdyP/uS4I+vzvPi3IT7zuV+KfLDDY8z26gVziXIzNyCmaSQMZvjoyHYa5WtdyQFCzuKLggF765JEyI1eYF+Cex/XpYDipniwXVjqd+33f5BuEgvkLe4jBt5IKe4Mhu9Cer1rN9kSmlOgcJha+B0j9RLm8HvQX57hsbWQR2XPGNv8USStx5d2PTwhDjnHeA8y2fR9gA8vUn2/uHRGHNPfd2vb6w3aXv0NViPZBr6m6Kv5KY0VaAK7SKfCV1RLz2VNX5Z+Q0XyHEmSQt8seblxNIjiFIkHBIj4Ci2cnoC5fAd/nw8p2gLX9taBP5crh36CMNB3lnnD9pBr8umg0pHitIDwc3v5UWCxYVPMP19f6qOgSTuG63fleyfWZxRdRmQq/H324BN9PSry3DHHHDIlFFpXdfrciMzev9ZbJN1qvbb/VSuLnBqjPe3EJJCO4u/hJLYQ5ECwxfWkIaVHIiO03Wg/g2GuE3HuKHl5FrO873ev1wsXkBsdEZkDPi0dQ+u00KcLwOB2kJrCYH4T13gZplDM6cXND/ChSoKIlYeyHucXmMfJZ4EX5SaPLp+RBVzBI8chZBoSApvIog3W3z1ooNXNeVrL1EFgKlnmP5xvbrv/9QDL5hzoXqJdLCu92/At67cP9i4qK99ZNcpyAe3B5oZImgwPghFJUZkGshJvZvIIUWgD9Idj9UyISAfZtaRbU39vtYgKXXg2iiufaCpEaG+TSS7DLA6Am7BpLdoSnRPVVA02ovXR1pbG+CZBeG/rw9+rWm4AVzSnNdv4+06ADhbbckdOuQR0tWeyE+/EWerRJdanGFVD5a+WVOfGd5b47H4oXzfV9kI50vNennRGFFn+eAfz6vDxSvP0/bttYg+jPXWqre0b99OPItU7l7kk/YxNN5Qq/ChzV+AS7DjXXzJg8tt9JIfxeBoO7dxX3//Fmv4Ab2yQVj/bpdoTYT8ZKchmfpakMWqC+Ozxcp6llZ56HVOz0T3ftMCpv763/cvaornbCHU+YutyWdgQ9hbXPmTP5hFclpFI39rAQWsIki6hd6YEdUmyGApFsqW34OopiKaI65Kf9mCOWiXq84Akmzfel4K17RDtf2bYTEoti/yHQ/2vC7IBRW/Uf0sKJ3FSxEj7C8Jdh84wowIi3q5kriD7TdfJLoSjgLHZwO6zFRP4K9CY9rfiS7kSug8kjOeHjGBQcSUwD2F6+/menDctzbr311ui9tA5Dob6I/N/zY1hrPDp/XvuH2zoGec6tDjfRr4eZ1D4TwQb8c2IpH8EMeAWNgcsIG5B26S1ePAr9NJvJvOaxkih+TRyT7AuZ2a9xuigqcuWLFRnyfk8CAJw8D1BASCObFjZsznrVW2PH0+0ux1cp2oktR63CYk16FC8NfrNZgz2xl/DXr/ghx1cBFhdIa5W679X6AyXxnuzuTJOrHqEl+7AjqmhIpl5qfYESBw4IShcG4sF1/Re8wfAj6JsgMJGUIugZ7dXpP/gW5hPojwo+U1A3yuh5+O3e3s89xtwb2QS5hakQ4kEtAw2zIvlEiOHIDcbGzXwb/YDUCdf5+SZUL7rxtN5xgunuaCZlIxicEs9Wc4oeYQvEC47tJF9NlgYbwmrMV8k3vUQjRbV8kuwYqJj0yQdngaL4GSc0UudCslP0gxUqVXh7id4COmpRnfX89+2ClB3t2BT5TtMRMPUQZMjcAzXkpDDcDNA1OcsBAKXZqZtCHPdq3tuWsvrvNOHI6cemlf2+8XvolXhyX+5oFcbHBPg9VV28d3jfIzNxOODaQ2wUSbcxI3kjjmBsWTZmx7IUJqX90vrUaI1KswfiYqFLmtTdaa+9Plt7YqLM+uDza40Se951D0garBTC0/o5J2KCnd+by4zc92BEwMwt2BolteICCo5HmisViXc/GZu3SP8eMZlrI+QOQjg8Cw4BhbBUJJt12PG4P6NT7HzxL8S4PRTCtOW3v1sHTWfXgYLUAthw0jjkNellm0tTuqxUdc9DjV/XjxxalgWbp4LE2Uwfiu+iXzyRpnbVqXvq5sg8CWYCNapyNyBsBC0xZgHvgQ+NVeHmvuUN8fAKEEHjXv1E9sFx7scB0Y4mRuv7buAt+XtH/MEcElE6F6GOo9qrb0kteYqTw8vQwy+cie9XDgy+BG48r4OIqyD0ryq3qAVAux061HlbpPFdw/dK2m/nJqU8PpvSeOBbB1hcdqHpGfByMpv/uteLGfITOeCvcAZcpi6uefphD4JfS+itZAhOc6Wyxbqtd7cQP0lpqdw/bUkeB51Lqg4Td2J9iNDMazAAnwKsm8+ac/65WJin6H5p+yY+5JGM/Ue65HDlQowCEeTQogTHBhA6U9DaQ7dbFF0yNEvfP+wcRYFqUeCxnP4YMpVIL6g3QPoH8AXDdmjfgyWUemctSbIejh6RZZmC8aemaTLQozqMvmK9uRws998ZyqXHVcvG7uXG0w+As2KivOm/1Uh7NqEMj9MeuaJscX/XUjb1fXJXWvx5qudNXSB2QOdpjO3lfF6sxTeyNbuCpd2MkUWY+keVOI2LPwLJNINSkytfALwUSi70M4x2MaY+bbQ7Z3Y6XMKyj/o7ibhW2+5/KTBNQTiYJqPFidUkMw2P0aTjKjulceoX5KUo4ic8QfmQOvbXFT5cHHtOGdOX0X349v77bGe+rKmd1ue2QkfPzyN+OeenS1CEi5nc1u3Q8mqdzXbeYV799U7vkUZFruE7aqDKUZxVEsnVu1nP5FVfmakcDKvmT5FenhK9Y179p6cVXRKAl7+gPwgVUsk7ezM8kTcopzhDXv88OGnCY+go+LBppDEGXv3mpYgc+BH3iFaCHRu/2j5D/O4GxUA+2W3fxp9Emw6hHY0T3+y/zb2INmR3lWNNs42j7Li2RBLUdEq7yvAIcRP2Xv0UlRvxS8g3NKsh+3IT/urL0qyvX49VqIuy/tN61r5U5lGRN4/Sy7b+0gEnWyhzYUY2GeQYZMRcez1y+MAWnEc3db6ciFGzlsjsM1rjTEFnGjcMBMn5dF9eLW8aU4h8Rqk75J/5+kqzKooQl77ZqfK+nNOZ8BCI9iHXIvgscEl9jKSdMcwTzr9hFJXWZo8hOPH70MrhKcjnsPdb4eYEcGQ9lH5H8TxLlXZUUUOnIZp61HH8oITeYkRc+WN1Ur9f6Ur7ry9PmPodBlUYqo/jtRSoAod/OG8n9bbOQC+9uThDpQ/pfAzygElceZJ73QXalF6oRi7z6uu1OVG91tV/7cNW7dIKinalsMSkWvW0fPq5c/3ET/NWhoiv/AROny1wad+K1AYwc2e58un+xuYtq2quB0+pBn9rIV3mtt1WMf0mI5KfdSSnY53GmCuiqyP7jt9iXJyAFdpItMYFzrLrY6Zz4fUF2DkdAkvufSVdfZg7IMQzHwOgj3DHFKSY51UL3hX86rHYCv+yQcuUdsn+JFX4okbrs3321LQLu3SbdGziqv0SVSQ9LOH15Pfqm0mdLQq59Wkqyt93BuuHBTSIF+yzyMJikTkr/hWw7UDg+QK5RUt85xYa+nmkQPbe8dF8mzfTAmm9OiEU8+83JJBZYfGXyi4WuavjKpFKLjmPnQRVhfHHQ9QnhsNOKTscfMGWr2ZXFdXgEfoyImIewJAARseu+e0EFZOdmnS4i6FPfwuqm3oDK+29BYJF/pkIGyT6YV6L8HkT98srPs61zzhZc2K6mM97OD8ISEXqVF3c5yrR+85LF2wFOkOiFyDWt5VIshTbw/GUoHPI2LxK2twMKdqdsSH/k+i7hu9t4MEI6L9QvAsGRsW/dnf3HrVSQaX3lkZSur4rl0XAXPBGmg3yH6wEiqCgEjnzFTc6LdE9gy3eXKkOPgRMvxDwpFw/Yb2JGiB39kzsocojaCcdsF75Mn70Ycnnvshn0RYro4hnSF0OvM+yx3Z7v84AzQQMOvyPLiPzvLUv3q4z9SZ1C2C2Ec5Li7naQ8iNARWOnlWrgM8Vukn6SH8N3ZMojMcyTCeG55H0dQDDio9aCeh7Vr85CZTdQHASnfZDnHMOOS0L/+BqDhyG/Sdi0zevkvBPkX3gEpRwruF9Hkd2tDz6uiLhIXaDMIL/68h2oeO64orJs79YthWE5X+jEu/wqHlhSiQ/7RPhAsDO28QZX9qMmwiMj0iUR0XhuUniWrdrB7H855NGtkf905DOQwl+6u9sdzwOYQ1OjKYcv58uTR+tAsajc1NOWTXZKR9ygv315m9BdhX/1U4bqblMItx1Chrqn/XgWJLFPBhkF4lUMIrrX2Xpk6B6L9MrxQZ5e5+USanjO0uIGrPm4IoG+8Ad6PzDxla3ZE4hwdPcRI24nYtPP8f7REZ7pH4LFLr7fykNN7FbME6NLPwebsAFNH/37njWtPl8M3Z1o4nOUzvJjSrMiaupbHyyc7AxczZMEy3b9DZSR85Fr7/xa1qmDXH54JRsLtAmwTAwbyh4QTBGmYPSsgU6xr4Vf4RSthe86ssbq88ETuAWaVzxpnX1aHh8kPkWptGBWBBi+31a0zRF+AT5boQ6bZJ575A+A5u0Hzr5oMGgyo16Z0dan+37bNnJD+KuzkmPlRQe2BdQmn8FSfPEsbNJs2avvxRh8umvqRYPyfNDrphIxnDwfyFW8XyE653X2JBbPIn00z+L/X4CXJdPNmUsFCz0f4I3ps7ROfd1mpxTDozQxwi30/Tk+Kdvj5GBiDnWLvxYRXxgJFV/pi7DJSyupR2W+i12sSXOqjaFv15VU1W/T1nDImmY9/WKs6zjIH6AOrWv3HJU8Q3T6wMZWxeFBpD+UeIYzOzp84Cj0OjQIsQY+x2gJmFOnAnPHgHH9767MR3qqbU+zHwHTvoMlH6HSUsxJbkZPaEpgNY8vUGnWMywBMKY6S99AMbRQCyJoTKDjdTaGLjAnjNN6xrzm4ablIab+MKGnRK4bCUnUAJF21VDvJ4wWAwhdtjdov86whDWf9J4XLV0PbgxQPwHwb9J+3dG+E8vEWD6f/ESJned7S8SX3B30CPIOFx6MrFfCdfmO4oIKkD2CNCCn3rfdggJpYjzRBgEUfD9+mHNv4diJA8vrNNHG/82e8bzCZIrmQhTYlSu9ZHf2L8bevdJW49O9TI3jriKtNgyv1J/x+O4ak2WWj7E+H/K//BD/SiXIyIm9UIb009e+BbhLtBFcqihlY7/MkIBNNkXZrOqzhrnavcGzTzFmXaJHEJ/Ea69vZTZKD5bnVaZ/IvTPjrUqf9eYdAsQK6hGyZWkxr5JHH1fqZciTax7xVCFPJwgVu18w/dROHDFZHqkPXR3L7Ha+eWb+ieSkIb7BSKIsVztq58MOeJZWPhDjbdtecs1QxXNtXE03aAjHbs+S29zWdE3L+cXPylFldR4X2IGSUJvHOD4DN+OGBwnFLJH9ZlSUHxtadMvP1sscF1BQoDmVS7gNcPYw4o7SyHzhb+bNNQxh01TN3TVn0LFO0LqSwxf7Y1mzXvcK7BPpS4Yv9ojuvJlZTTbGl9F9cAPJMSCopDYQIB05VSc8ttgziPbAf8Lafm9V86B7L6BnbLHBQ6wO/9alugGsgxsdvPLNmCDS9RZQJzzfyiSSw9YL4vh9zuPSkg4ogowVeNHeqdWPeVKucW5XvILi9dia+aQH4jv1Vip7xMpuooxVuCNrCBbweqX27+sOL9b3qgavC21vDHvoPo8HJ9WUAUPvIFNv+hqAtGUShw/7pAwBBJLJs4/RaLP0zKHJ0pPXy1X8xrGp0kzVqc0rCtM4F5jnmwfEnVBr5U9pPNksCd9x48AKr0htnYZs8QIp6h0Hxw0lnByGER4BwAMLPPTmK650hiCkSFOaF8CX1aKu0mSpf56352Og+k27qa4E/9DO835Aoi7POWbE7H9H/0vpmhYT2DIyz/iZNMBL3NCBU/pBuB3zHv1BMinwSzQVPAiXmA4+K3UtQDOfSL5+ZvgdBBLFxQaAkfinn/WUsR+YWz/BSgFPQIevBhg8CPf6wX0+oA0xwCbKCG5KNSggjfYDiMUZwwheci0krgemML0Y6i2qxWw+RC+SdiFA2k3DF/uv+4grErvVLMgRMWPecuVnHCdEEhXCI5wPWBoMAEELpg9VgY92ibb/oT/heb7jJpd147PuW/NhbrU+N3JJOhOLkQnxhP5EHeODhTYcCMFan1g0Qy+8SY8N/svXTrD8r9LxbBj6i7Fb6/6pVGUcQnyq26lOOs++TDII2BLdHFC7iPM6uhk/JcMLch3TBfJMTLy49njFLw7pQ9adwUtaDMJkI7Z36tyD65KSH5CJ8Uj0JWBL7MnjsyjX5es3e05e/CQlm0aOoM08ou3b+IQiq1yGSByO+WB8pa1eS5Dl5956wn7IRR/q8rtWjOTJUDi3aMws9Au0IyQm1QA55fT52HIJZIv/MJZll6LDqdszs7nvif8AiqGDuVFxYZznkkf6+rzWtBf9gnUbKOzfBSTfjqVr5qdljq4foK4frU17cx9xCtWrfFpvvW0qsZuqEqTy9agRHcMLIN+NnBV7uuEK7Oed7OkXctymfImPuEzR7GHX1dBo/pqVwc7HdTg3+t9qz/RaJ8nl4CBoF4Esv16DvPtHcShziatPe2lmWE6PYCPG8QqnsfAuiJ/sBmXMSHdLjQNkUpMX+wbVnOkTCgBUSlzulCOVlJ47Ma5UF5lauwy5prwF4MYRt06x3e3LjVdd8nSlJc1OL0FzwYetnVFzV6+rt53NjHDriVuK+/8Edt201zmTUNsojbXeIvb28W3/VFiavM0nGDhzucJ5kyczWltBOnZrezuHdHYNEGZOKKlWoLRIDvgrjclsVAb7KMfOUNtCfMZwZC8zP1iT2SJRmmoJ23ttJmauy5hJ8Lu8p23thhK560M2VKo21cW1XrCP272l4/18khSWr6KfmvMKvlZOB0AFDoCaRFgztA0viYLf27gbHlvRTX1Uo2S4mbNyeQicd+6+Kw7vr13ixarYEk=
*/