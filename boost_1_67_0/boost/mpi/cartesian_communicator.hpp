//          Copyright Alain Miniussi 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Authors: Alain Miniussi

/** @file cartesian_communicator.hpp
 *
 *  This header defines facilities to support MPI communicators with
 *  cartesian topologies.
 *  If known at compiled time, the dimension of the implied grid 
 *  can be statically enforced, through the templatized communicator 
 *  class. Otherwise, a non template, dynamic, base class is provided.
 *  
 */
#ifndef BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP
#define BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP

#include <boost/mpi/communicator.hpp>

#include <vector>
#include <utility>
#include <iostream>
#include <utility>
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST

// Headers required to implement cartesian topologies
#include <boost/shared_array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>

namespace boost { namespace mpi {

/**
 * @brief Specify the size and periodicity of the grid in a single dimension.
 *
 * POD lightweight object.
 */
struct cartesian_dimension {
  /** The size of the grid n this dimension. */
  int size;
  /** Is the grid periodic in this dimension. */
  bool periodic;
  
  cartesian_dimension(int sz = 0, bool p = false) : size(sz), periodic(p) {}
  
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & size & periodic;
  }

};

template <>
struct is_mpi_datatype<cartesian_dimension> : mpl::true_ { };

/**
 * @brief Test if the dimensions values are identical.
 */
inline
bool
operator==(cartesian_dimension const& d1, cartesian_dimension const& d2) {
  return &d1 == &d2 || (d1.size == d2.size && d1.periodic == d2.periodic);
}

/**
 * @brief Test if the dimension values are different.
 */
inline
bool
operator!=(cartesian_dimension const& d1, cartesian_dimension const& d2) {
  return !(d1 == d2);
}

/**
 * @brief Pretty printing of a cartesian dimension (size, periodic)
 */
std::ostream& operator<<(std::ostream& out, cartesian_dimension const& d);

/**
 * @brief Describe the topology of a cartesian grid.
 * 
 * Behave mostly like a sequence of @c cartesian_dimension with the notable 
 * exception that its size is fixed.
 * This is a lightweight object, so that any constructor that could be considered 
 * missing could be replaced with a function (move constructor provided when supported).
 */
class BOOST_MPI_DECL cartesian_topology 
  : private std::vector<cartesian_dimension> {
  friend class cartesian_communicator;
  typedef std::vector<cartesian_dimension> super;
 public:
  /** 
   * Retrieve a specific dimension.
   */
  using super::operator[];
  /** 
   * @brief Topology dimentionality.
   */
  using super::size;
  using super::begin;
  using super::end;
  using super::swap;

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
  cartesian_topology() = delete;
#endif
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
  cartesian_topology(cartesian_topology const&) = default;
  cartesian_topology& operator=(cartesian_topology const&) = default;
  // There is apparently no macro for checking the support of move constructor.
  // Assume that defaulted function is close enough.
#if !defined(BOOST_NO_CXX11_DEFAULTED_MOVES)
  cartesian_topology(cartesian_topology&& other) : super(other) {}
  cartesian_topology& operator=(cartesian_topology&& other) { 
    stl().swap(other.stl());
    return *this;
  }
#endif
  ~cartesian_topology() = default;
#endif
  /**
   * @brief Create a N dimension space.
   * Each dimension is initialized as non periodic of size 0.
   */
  cartesian_topology(int ndim) 
    : super(ndim) {}
  
  /**
   * @brief Use the provided dimensions specification as initial values.
   */
  cartesian_topology(std::vector<cartesian_dimension> const& dims) 
    : super(dims) {}

  /**
   * @brief Use dimensions specification provided in the sequence container as initial values.
   * #param dims must be a sequence container.
   */  
  template<class InitArr>
  explicit cartesian_topology(InitArr dims)
    : super(0) {
    BOOST_FOREACH(cartesian_dimension const& d, dims) {
      push_back(d);
    }
  }
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  /**
   * @brief Use dimensions specification provided in the initialization list as initial values.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  explicit cartesian_topology(std::initializer_list<cartesian_dimension> dims)
    : super(dims) {}
#endif
  /**
   * @brief Use dimensions specification provided in the array.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  template<int NDIM>
  explicit cartesian_topology(cartesian_dimension (&dims)[NDIM])
    : super(dims, dims+NDIM) {}

  /**
   * @brief Use dimensions specification provided in the input ranges
   * The ranges do not need to be the same size. If the sizes are different, 
   * the missing values will be complete with zeros of the dim and assumed non periodic.
   * @param dim_rg     the dimensions, values must convert to integers.
   * @param period_rg  the periodicities, values must convert to booleans.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  template<class DimRg, class PerRg>
  cartesian_topology(DimRg const& dim_rg, PerRg const& period_rg) 
    : super(0) {
    BOOST_FOREACH(int d, dim_rg) {
      super::push_back(cartesian_dimension(d));
    }
    super::iterator it = begin();
    BOOST_FOREACH(bool p, period_rg) {
      if (it < end()) {
        it->periodic = p;
      } else {
        push_back(cartesian_dimension(0,p));
      }
      ++it;
    }
  }

  
  /**
   * @brief Iterator based initializer.
   * Will use the first n iterated values. 
   * Both iterators can be single pass.
   * @param dit dimension iterator, value must convert to integer type.
   * @param pit periodicity iterator, value must convert to booleans..
   */
  template<class DimIter, class PerIter>
  cartesian_topology(DimIter dit, PerIter pit, int n) 
    : super(n) {
    for(int i = 0; i < n; ++i) {
      (*this)[i] = cartesian_dimension(*dit++, *pit++);
    }
  }
  
  /**
   * Export as an stl sequence.
   */
  std::vector<cartesian_dimension>& stl() { return *this; }
  /**
   * Export as an stl sequence.
   */
  std::vector<cartesian_dimension> const& stl() const{ return *this; }
  /** 
   * Split the topology in two sequences of sizes and periodicities.
   */
  void split(std::vector<int>& dims, std::vector<bool>& periodics) const;
};

inline
bool
operator==(cartesian_topology const& t1, cartesian_topology const& t2) {
  return t1.stl() == t2.stl();
}

inline
bool
operator!=(cartesian_topology const& t1, cartesian_topology const& t2) {
  return t1.stl() != t2.stl();
}

/**
 * @brief Pretty printing of a cartesian topology
 */
std::ostream& operator<<(std::ostream& out, cartesian_topology const& t);

/**
 * @brief An MPI communicator with a cartesian topology.
 *
 * A @c cartesian_communicator is a communicator whose topology is
 * expressed as a grid. Cartesian communicators have the same
 * functionality as (intra)communicators, but also allow one to query
 * the relationships among processes and the properties of the grid.
 */
class BOOST_MPI_DECL cartesian_communicator : public communicator
{
  friend class communicator;

  /**
   * INTERNAL ONLY
   *
   * Construct a cartesian communicator given a shared pointer to the
   * underlying MPI_Comm (which must have a cartesian topology).
   * This operation is used for "casting" from a communicator to 
   * a cartesian communicator.
   */
  explicit cartesian_communicator(const shared_ptr<MPI_Comm>& comm_ptr)
    : communicator()
  {
    this->comm_ptr = comm_ptr;
    BOOST_ASSERT(has_cartesian_topology());    
  }

public:
  /**
   * Build a new Boost.MPI cartesian communicator based on the MPI
   * communicator @p comm with cartesian topology.
   *
   * @p comm may be any valid MPI communicator. If @p comm is
   * MPI_COMM_NULL, an empty communicator (that cannot be used for
   * communication) is created and the @p kind parameter is
   * ignored. Otherwise, the @p kind parameter determines how the
   * Boost.MPI communicator will be related to @p comm:
   *
   *   - If @p kind is @c comm_duplicate, duplicate @c comm to create
   *   a new communicator. This new communicator will be freed when
   *   the Boost.MPI communicator (and all copies of it) is
   *   destroyed. This option is only permitted if the underlying MPI
   *   implementation supports MPI 2.0; duplication of
   *   intercommunicators is not available in MPI 1.x.
   *
   *   - If @p kind is @c comm_take_ownership, take ownership of @c
   *   comm. It will be freed automatically when all of the Boost.MPI
   *   communicators go out of scope.
   *
   *   - If @p kind is @c comm_attach, this Boost.MPI communicator
   *   will reference the existing MPI communicator @p comm but will
   *   not free @p comm when the Boost.MPI communicator goes out of
   *   scope. This option should only be used when the communicator is
   *   managed by the user.
   */
  cartesian_communicator(const MPI_Comm& comm, comm_create_kind kind)
    : communicator(comm, kind)
  { 
    BOOST_ASSERT(has_cartesian_topology());
  }

  /**
   *  Create a new communicator whose topology is described by the
   *  given cartesian. The indices of the vertices in the cartesian will be
   *  assumed to be the ranks of the processes within the
   *  communicator. There may be fewer vertices in the cartesian than
   *  there are processes in the communicator; in this case, the
   *  resulting communicator will be a NULL communicator.
   *
   *  @param comm The communicator that the new, cartesian communicator
   *  will be based on. 
   * 
   *  @param dims the cartesian dimension of the new communicator. The size indicate 
   *  the number of dimension. Some dimensions be set to zero, in which case
   *  the corresponding dimension value is left to the system.
   *  
   *  @param reorder Whether MPI is permitted to re-order the process
   *  ranks within the returned communicator, to better optimize
   *  communication. If false, the ranks of each process in the
   *  returned process will match precisely the rank of that process
   *  within the original communicator.
   */
  cartesian_communicator(const communicator&       comm,
                         const cartesian_topology& dims,
                         bool                      reorder = false);
  
  /**
   * Create a new cartesian communicator whose topology is a subset of
   * an existing cartesian cimmunicator.
   * @param comm the original communicator.
   * @param keep and array containiing the dimension to keep from the existing 
   * communicator.
   */
  cartesian_communicator(const cartesian_communicator& comm,
                         const std::vector<int>&       keep );
    
  using communicator::rank;

  /** 
   * Retrive the number of dimension of the underlying toppology.
   */
  int ndims() const;
  
  /**
   * Return the rank of the process at the given coordinates.
   * @param coords the coordinates. the size must match the communicator's topology.
   */
  int rank(const std::vector<int>& coords) const;
  /**
   * Return the rank of the source and target destination process through a shift.
   * @param dim the dimension in which the shift takes place. 0 <= dim <= ndim().
   * @param disp the shift displacement, can be positive (upward) or negative (downward).
   */
  std::pair<int, int> shifted_ranks(int dim, int disp) const;
  /**
   * Provides the coordinates of the process with the given rank.
   * @param rk the ranks in this communicator.
   * @returns the coordinates.
   */
  std::vector<int> coordinates(int rk) const;
  /**
   * Retrieve the topology and coordinates of this process in the grid.
   *
   */
  void topology( cartesian_topology&  dims, std::vector<int>& coords ) const;
  /**
   * Retrieve the topology of the grid.
   *
   */
  cartesian_topology topology() const;
};

/**
 * Given en number of processes, and a partially filled sequence 
 * of dimension, try to complete the dimension sequence.
 * @param nb_proc the numer of mpi processes.fill a sequence of dimension.
 * @param dims a sequence of positive or null dimensions. Non zero dimension 
 *  will be left untouched.
 */
std::vector<int>& cartesian_dimensions(int nb_proc, std::vector<int>&  dims);

} } // end namespace boost::mpi

#endif // BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP

/* cartesian_communicator.hpp
+k53ip1eBLBK7N4Od9g2sL7FKr+Uw7aD+dc2stvfhKlD4exgav70YBr5N9l1QAoAEUo83y0wCy2HhJMFUxitad44aL5wTJ7ATBefCCCzMegAgjtjJgDa/wLL9r/Akv0X2G0k/+CxlkDD7gQlgOrhccB/cdX8ISJ7eBwEUjv0+ENReHf58K7uL8GxO1zuS+QHTJlOjgOv3I4PV/0H0mIX4EOa2QBYkanVuXIRJ42RG9vn7uRPYDmluEHAcRN7YKzjcdKfRMb/8nf5I/MHlu8Z2EKK5EtFuGy72cI+S3ugTCW++pLEE67QRw6tXdpfc6OcwzAhj1mW93Zf2nfJ36/9hv4yQ9Ivtq8ZJtR5vncRg/+9AYiSAZYndy8Kvac+y1C7LDw0LD7EeXxMfD6eM6SjU/WviOuEVeq9jkum7q8YjryBmEryTHP9R2PJDt5pfWv4uysqIvE10Rw4h6c9bfMGQVp9x6e3tl56NqrkGPJjpgUyXo0kacMpolmmc/5y9k1ILb/ViTxy/0HufTQsh37aY+ZWNYa79FkxZ+Al8uLmreqNXEfsJL/vKPSxejqAistMN3N6T2Rl7SLTyT7qsPxiSR19+huLmVQFTV3+EiRBTm6fRdLkPH79rQ/VheXzKGuvbMahtcIRw5Oft5zVm20NIOmLYe2C56hEFlmc8Ng+wAKx23R8uMHiaRVx3VnIxnywPCRVf6Bv/HyCpXFV5OvepbwPWlu7m9SlQtjo8yXXS7c+3XaLoDsE+u+/9DJIeniTn7vm3fFBMU251RGoL3Fl5TW4f1X/r7qFch3ONyOgyafscDpVAQN3TpZaJ3e7Cp7lorKiTF+28O8O5iTAyxd4LMGy1Atw9mGFDMn4DgIhPbcWGag/vxR4032LR9tiQddGZE2CH/2q9jtdUiEqtdB3RbebTo3/TtC9JRFe+EflsqNDDczfeH4Y5r/7P/j0P0iYF598/ltSuR+zObAgV/nyYhA9FocIsucGbEf9+q9yr7Ump5/31P1xwew1R8c+DWr/6VKU5v19F2KKAxJw6rd/d1rZnUtPXtWdcTvmtaVc4FupI8GRQw/kkrv/RakzUAleBMNT8KY05hYNXeS/frKj3+PAPTTMCObaCdMwgSJD8CyeihCuEbo/gzMsnlg+dOODsXZqD0l2B18fV/gex6/9GrgZFqvk8Hb55KKrVCOB2GqaB2G2UnbCxuqyMHM1KEtSBYuBoHy14mug/KC+hKFFt+oviTesg6uUSx+9bVGtCPQq07rNIE7TlTPWkLWYPMOEDlr0s8JCxa/3p5VH70nVHmyzt8NedgeVYiUJY8GGXNlxmQvb6EmvutaqwM158cfr84Xr0mkKyyHuSkBVgcJp9v1zPNFn38Gbw/dtdvpLdU4cIgOO37XoDrTbNif2xd1ucDo1PyrnQ7F0SH/N3fJ6f3rR5RT7t5gRzJTxXWok8QTuRfceGJMNr0y67DX8X1NfkcKKFTX5kmDMhEj/uWWCWJJPgNYSDYWU6vTbSh/yQVJMNZLptIKC9NdBspIltXicaYVo8wXqF3wugvLbiSZ1Zg7qnCQJzLo6v+bPb/9626y5drNxJrl7cS/j565hih3b3YuCwjEW7leX1y0OoOfL9RaHNP22pdK1xPZuurZuhrNKbwM3v0mt2s8UyzZDw4+Ztyq90vdW5ntL62U2Q59Ws6ZHZWQOYYsk2QCLpaQVyMsxlz6b+jZoU8JvK0/Zb3tm0XLaMIEOaK8AleV+YdYF7r/ItFnACDLffbjenivAYBWhWr3p56if65CGCqh6dUStFF6eEp6h3xr4C183zl6l6tByUcR0bUStJF5eAk+3eyx7NFixKeOWNvf99nN7j9Gh0hrXfZZ4JtiH6/bZeg+7RokXdHoMHjfovXVIOeZFmOjawau+g1jEt2FD1CqFQGgcz0EU9v956DNQerAbx+6zjI82d9T/98jAErBXLp3GFeGSs4+4HDlvwPfDFGv12IvoyJ1Sv0MYRSgsoeAhjBXG4osNQYVQNQGsXkxvGnald0FGVnsRPXmbcaC4nu2CKEtSKCrkK6Rj0d8vjxsWXvEqjXJvPQnmrjwFOSnAuopOQWiTUCKuN6XfT6CyVZjq2j0w4y2vkuId9rkS9kJvLbLDtPeGcNM/zVC7LZl57pFw9Kpf1OZPVBwFSNtnlvC9V7p/7xXEB4rcf79BOyreOU/3kXzL8OnByHiTeMvgDSD63xaNtj5cWZDD1ZqQw7Gbb2Ea3DUygQ4zIRpWd+ezB8tZPKAUUkPlRpCkl9/igGZhxHRpRK2InS8mqeFPUlhp8rKmgq+/gi9rJji68bbJxdfYCZJyi8R162a1d74wsJzC020fy079CkuqAGNZ753PDiyXRrCn83T7x7JHgjW0b2OwcGRJI/xENQnity/T6BmfwMNct9Jct3E2e3nyJDD84Tz8YSBIqFsqo8Ng8AVkmAKzVoBwKEAaMsH71vsgMxLYp21jECmwjwcaSHFTuWc4M5C3MAAqiwAy2kHGm28pbhWEjAfprzz0STwhKIDBzlM5G2h8nagTLL3pTx7QZP6J/uC4cHXifYf7O+8HrbZDtPX7mTUKkda7+dgl3oG8L1J+jX4mk6BgzWjKicW7o18RLiTDVmKoD29+kS9eWTauuNyuE50y9z+srn+uneCf8MIu8qyXUF5LChMX3t8+HNMzxcK6H6YREkmqjuGjSG6EjCJSxceXndMyazsiX65L/76/Hbx4I99/Ba/53fkKR7Wdo0KhqyzTyw0ZxwHAuf+ISzpRYJ516vF528R4j6HNf+Tlv1RFyfj/9Fsi2H/ZLuQCPvaW22iAAGYvITfDO2+7tZpvbamGiCBsfzgoRWayf+phxy5v73UosE4GT4kRogoWBddyWe8xBoEgqFdKO4DiBzwQK5jfTQJ1PQv//fEVuqBt+1haY/JQaq+DRcbU/FxKvn7ribkMk2oDPHI8/1HiGntnHNnA9q9QuVJ6n0DYCSM5hHL1dJJAfhRu5CFnoPRWfjmE4puQf2A3jp3BbJzmi4BgLe37Y02xxoztzzq89N+s70rvAB9aX/2n7qR3fHakd7HL3/MPw3Yt++P6gbtOCkKlu9NLu/5YUCx9IcvduB4PzB2o0mXUrd+Ee3d/DpDlHYy/C+Vie53/+jq/0AR17aIwB+qAOcANFjAMWxHFjlxv1OVpk8HHUpM3p3Oocj8eU643uQ1J7Uy3etxqDRE768EG0e2jSOvK247qddC453f7r1G3yw8HmjeGY8dI28WX7WexHWtLVQeD2335obJsXEW5rLLY+JjAhsVcSXWhnIk0NT099lS7Yxr3ppbes+lfSDTBa8DH379/FUJInFdT46ITSY6Z5QZNJWNfeUYO60zaSF2SiQ7rPQECdUfnrn4PKnJ0313KWaC2d3MGjaPkSiFMuaQtesC8QpbY2pbgaeBBpRl7nFJp1Suz+qNPRJzG/ZPxLIyiqXl6leG6dlOF3CkZTxGY1O+RTER6WO9Dui441h/r3KcyxZAyHhJbP6xi75gsSHqYXyi0x6C5xZwmCXt0EaEZObaJu3kzvFbt1k2X7sX+nofImz4sCbM0AJPfuh/J3LBOMPcgTOhLc8CM2fbOjXIR/JsMjnImMHoB5Wn71yYGyP4lBrGgrDYiSJM3P1R8wm8H5fwQ7JP+1vsssHduSg63bXI7SznV0rJV8tZmHx/ovej7wOVAgX9Zm3QOsBHM+092wlRyHcGmzb4w4RrYxCCE2mScF7wr4OXPYf8f+fM/Yj3O66meIwRKrz8k6SxSzDWUsHtBNlSnn2Yv+Y/kAbVyDQds/yNG/59a6ZJHwtzpFH2fvbW8unLqIXwQ2//Sm73s3XochAh0pz8Ku/Eoe5cZV+qh+EMRCmxhy0UC69/Q3ADVKyPo0UDI/vhQUIXfLIDQ7riBD9rkDNOqz5neAy8LdB//e6wF9tzWuvlO7x5BkQxUz8G5QV5U4Aqd4WfS/4rx2C/2mj/dp5fe93/rW48Sh/QJ8prlQfsttP/ZEfjhmDbv9Q2t5fS439AT9Zn+5nzBv/mwNgiADCKBejdd10PEwH43QTewf9J4Sp8gdGAqMNGz1Z5TP3vIfx1kLPfhvTD5nuiPj1HcBmAsXXrwdpvmOc75yMkJ8jzyXhjopUoKE3aG3XzzwNwDX6e+hS0vgXro3cffC+f+I0qXqW/STdXAPxQW//+VykS7UysZDA34lC41jsZNX0TAv278bq5/vaWkGmIDcbopoKy/QX13JDst/dg9MKs0ulw6MDl48ybM3Xrvtn86lCIYFjgHgvr3Oeo+413abyghWvEv7DaD2GdHX7AKrpo6Ds7Vie6/gRe/ZHisv9KA6bnHjtvsJ+/1Wo68anTvhZZzrqD52+4ilN2ssWAU2+MgK9Dguh6YV4AhGIrtJPajtf4+06g1tgB2ffCCPpbn2AYR8eomckzuj70LLLxgSxu3hE1n5uVpNHo8sHiPDnvMvQcRJVyslWdOD9jus1cl5jiLWGS89WpyYP/1ffRZercf/HKmgHHgE3Zz337MHEjP7avSn8blq92vT+IwwTl3xz612N3lvPnGlWZ/IxIz+3K5bI1Mb0Dd1PXD/S/safl0gLTnu0N8qji4+0Ui3P+xJrcoT0qkOavYsMvrVyNpZOSzZKm1Nt895ytBoWH/Xorq/fsBRbXI14rzgsMIEZVfpNNOmiiD10gLX9almtgidNgLloLLuGXGR6eVz6nfx1p+c/cNV2mq4HkIuzZc6x5bnN0lbB9NDMskxBnPBnw6QNh2yEONGsFYn/BNbqG6o9bBalsf0G21sxAZW7OnpiCwy44b4+GkEFGpRGnylqxe/M/xe63I9786Acs2iVBwpuGBinpNeb5rxovnnJkwAbLAfi/t0gQORT7xBTFH/B7bKVuT5zx7bi9iOqFsb/pSLxrfb3q9rw1ZS4u2Ju0Lkue+g0O23bCmDaLhPcHZXaWrd2MhmqLjPQ5lFXzuodcbt6r1p54hv2TGT65H0Qozz5Jdok4XUIel5YjEMqWEHxnp+12/BM9LjPchOQ/tgn8plpw2og4H3G8fLJgaXjIea8yjoZYiYDVNWoEJ+XMYLVNOXdFKs1L57w9ce/mTnevlS6X5/H7SZGMN4Mnzt2QoghyRZ54M30TteX8rL+e7/fDmDQt2weX/OuxYgIdZeta2n/nrG3X2tz3tr/SRAoql2bbz/MzZHAc3cs5i4fSJzhpZU62OdHW1lQcHNIBfjMeK8xHoll8udcSefwjXJd+rz2cQKJKKr8MSXVAf9WT5+UuScKY+nP3hRKPPcL76niO5yzL73TeEFEjLP854bFOyv4ZIH5R6C0h0IbQbhin/mNpkPAacZP+VsMDgCEtVWfZPm40lOyoZ0ONcfenTlh53JOQ34AthpJ92jQzeLzFnCMuW5CtmtIw5TUYrzU6V4duyjOsYAIb9mNKZv0UdlpO71j8wK8wdS05ymAqIKwhZFKsS3XE9mKDavcM6jv9Xq/IFPzp7Px129a8mzyB52nE17o6RjX3LaaCz+/iKXEUION4MFiAgmn7e6JCuenNYMBx81PR9RDWP9OL1RHOZ1k8u/n4keqM+UVnnx3+PA4a4+8MQOwO9tBrz2sAi/f1C1GvTnSTrPhn/tQdd38ZM5b1lClCHyYBo7nqNN/Apb6nTt/A6Sed3eSxg09UtBKD0u1QdLwOO981rbrn59lhGJvjOEPuEHftX6LUbKQyl6pnsevVlK5LdCWaop1+Xxptp3t+UesehZXPYH3eJLUIJE37BvYcDGxxFmKyJ9HaS+GK4aEYs5hH+JngvT/ZSHSRJZ6/wJLqnJcDmMNS4tT6qCSMQ6re7/UjAbppbvId8b/ufY1rlP0cb+pb7m5VIteKGtmvK1Xr8m8t2ApT8CuF9eMCSWQr1YcXjACok8BG6CQA6DKIGgU4OLM/DiYKke7JyfOtzwdU7Kjd2iuQ+iMfzXQP7O0iKuZ7JYN0dmRuA/3pv2hO1v6NmODg7yVJYCnLd49IDvDp4icMDInfiQNKDfkHHEv4koQns+32D6nwP7yCJsAx46yXJ6cSFzAndwoE1IuJeRUE+XhaDDAisjheAukeGqeHC5/TjQr68wBhfEePKF7u7Z/M8wmIKoBTKv+Gx0u0WqTjKCr42BX5v4jqFRlAmnQ3QaQSl+j3mFZVWxB/qJyBCOblOerudxNHynWvD7GlilgMME5HuPkd8ebbvYNtWIS7FVpj9FOQUZvZ1q+zV1tyqt4J9ltgn7+7+XcHC/4Mb/vX3Yd1wATohZ3///bZd8MXvElR/ZTOKvIZMDhGEjQswJE3X05dNHGddmJdTBCWT0d+D0xD275QpTmgrlQP7z7TDIcjS6M35yHjWP+qXP/NM+x17oetQYFfdYq4hzaptDP3jZORtiVXeIEnmvD5M1xOmclEYuR8lZGfnUNZsaLRVs1c8rSWUv+d/RMYkMtH5azAt3aPc8xF+zIG3hT32iQxMOF3a45NO/9/E8hzwzOHxjn9PcfQXSnlPeqNOqOT79I5dBnpOTV8+d8GervkYw33/cjOIwiz+qdJW71VXTV0mx5XWJcPfUHf3XUloXWLTYYOdDDZv6inSHTdNwRfGatkYr7yXZf+FvYtyevOaWGk8l7IbeQOle3y0y39PUzb8rffazXnbP5p+B/5mUfEKiLuP4skLvmYiFbrBv6XZEb3xINvge6G+2+47xq76lWoe3WVFBjOK2gPTpz9XekK3tXx/9OIZ5oHjY7fZedL3U/gMxUiViG+rmvZkLiBwUJVVCmPAB6B/1GFexyXNnS7rtl/6mk/mOwOEU9dTZMty0EdjMZfwyJRpa1ro797+xLC6b8RLUWTa+8rerzFwunTKLUeexq3MEQdSXptQ2mfvezfNC6AFdR0GJ5EFL7ay9RHE1mJPWlqv7t7FK6fD/yiTGXXO+YioIUObvXQJK6rpU1Wx3YfGST0LXN3o4alhtonDQUQlk4xT74xly8uhVzEWzrQRmK/v096EYFmdGA4Fa93zDeqg66dzzKrpc8Jx+N3gWn7t5LVkTkYrPZa04KQGeoLaqOxpdl9//5oeBRs2VR/pW8phW9cLIfWvfdL3x98Fa7nZFcszxz/2veyk3bZNkL+6mUP+xC7WYZeDT1NuJyg2oOuAjLdGD7fAiYwWS04YxRACaywK2/+OQlblAF3VDjOGUeRH4NA+JsbDiZZyy/aU3RIT6ThNV4nBx3QgxCSSm+a4I+iZ9NRh4aT+aEDiXu11846mM6qQMab66WoplzyBu1wg8SeSp+knLtoXGyYP2ar53B9/Zzjf/K8nOqe7sHnxnrLfg/h9r4+9gDB/l+u39pDxhs8IYr0SxLa5K5tBMEi/t5b7chFmXz1Nai9Z16gsS5Vx64vfxuQwMm9qSmaWmeYEj/XhSHM5x/peejXrHzuNiaXPDZOKRll4DTGa4RuIzS8c6xAylfUPOXZfbKefegQefedWrxqEua0xjIAPVRrV3nEP2T8InE425K9yQqp4g+sQ7RWf6NgjBrscaQ/bMvxmx1I9D32lk51R+hjIaT+m7cxWePEU4jeDotYUYzSQqlUf8glXpnQlZRvDuK0PdX7quAGl1SZiGz5fpdAsh6FPrhU01Mgbdek3kD8lurl9sMmzEKZQidFepvtnP1Oln3LgYfrh3GJyjf7LCf31QzbkYFmY/ubaVkqOJa8xetX27evRb1kFnUpK6V18GP+630Pki9qxbKZDPoy8Xf9pWwfmH+lJ3Hnuvu9bl9VqzvsKHPKJWO85D/cA0b1JuxWPej7NGSpG3B6dn5vsx6QbhmqadLmcJqc/9dW+OVieFyyoB+ZV4Nz7oIAnkWu4KJJ3Jw3dzD3/0Dq+Hz2mA3oe0158ux4cKIwhUcPS/OTJ0JQanlNY/wABZ65L8FGhhS+aU8vnWuorjn3/PYLKySMMF0VTSB5B3vXm9VkfhL0G4bIygcJN38QvBsLnQ5KF7RYIvCXpfevZ3tuoaBzYXsbuz++1wqmmGERfzBPWgm2W+IDqpnAZqOwRDJ2y6vzbwtd7jz9Nh+Wyuv1Q+ZcL1K0KI6O0ZulWgT3FAxW1cjpSjuTyHvMhDfsv8/KnLr2N7xqmr41P82LQNmM1j0r7rgPpaOf2wdcudNuGXoRHqAxFIXQ6Om26eD1fnBPznjsF8mx9CkrZUpqfUxJIZ77jlH/K2WEc8OlFififI2SrFo6CjhwZIKU36aVdFed2+EKRDsOlIOzS66kPHcODfN5bdQmGyQxc7lRGEAXoRhwHsdNdfVCivYLLU+gk3ZDaQMsV6/wglNOKAdEjr67taQjv6I375IA4TWdQXJznKdia06okB3ByM8iBiDjFyPhM5bC/QLgt3g8XONNhSnHL033c9f481GUXQuLvathWT4Kl40958Pqc+lceLEm7BBmDw9KdK9Etn9g59t8H9C2EbNoOii18qZzMY06hZm2eVfaGjnR/wQnwnA48jbX3MTqvDR8vy3PH6MtSYButWWGdHmx6aybaKs0Mzu22BR58zu1HV/bG7ydXv/aew6QXswCBQLli4DBFwu05J3NtxGFXn7/3hkgzCEjVC50NDmiSLyoznovfgDldDEKnNypXYCrTDteRF1OsSeceedILw6/ff2Pf/LbC6tpG2/qxgbRF2+a9vI0DozAb2tteOFlzWO2Sft1uJGvPaETfFNNpeP7l6944DhHQtkg0tPQWEYXxshoYbuu+lc8Iq+YZovgFnvZwZQJcaZ6FlHyZXnWLzPdIxf1aGymeuOf81Bzm2ihC37KXg30oNkBpNo6wrVeRZOCGgcqrmbczecd3YQXPVkFN3GKNFZQ78sJHgT6tHLltXps3h4GgnShaTXoeagje5+/v+jN/WjXW2NBhlaN+9BulB1+G53X2/HaOLc6HKr3hF3u3I26ZqoqBPFnAkF6lP7pPxrDhHgKS3MVRS3jdtou8ix8pDQpHKNqHC9v9ViEiIorwi2t+eZLJUv86PpJLrM/zxh7jXg6n9ocBFOauh73H6igwHJve6oBgwsthAZwEw01X7rc67Zal8WfQ2OTrG4VcTaZTCDjgswMNOc9+/wDKJDgRmOq7Eq2JB7Id6ojQXcosrlW7+8pZg9OSeYu8V27RmdQ6Gb2uIZtrP5SGM/19n3xv1WJDaaN7yRWgc5fdVPI2m3g=
*/