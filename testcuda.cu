#include <thrust/version.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <algorithm>
#include <cstdlib>
#include <time.h>

using namespace std;

#define USE_THRUST

int main(void)
{
  try{
    int major = THRUST_MAJOR_VERSION;
    int minor = THRUST_MINOR_VERSION;

    std::cout << "Thrust v" << major << "." << minor << std::endl;

    // generate 32M random numbers serially
#ifdef USE_THRUST
    thrust::host_vector<int> h_vec(32 << 23);
#else
    vector<int> h_vec(32 << 23);
#endif

    std::generate(h_vec.begin(), h_vec.end(), rand);
    std::cout << "1." << time(NULL) << endl;

#ifdef USE_THRUST
    // transfer data to the device
    thrust::device_vector<int> d_vec = h_vec;
    cout << "2." << time(NULL) << endl;

    // sort data on the device (846M keys per second on GeForce GTX 480)
    thrust::sort(d_vec.begin(), d_vec.end());
    //cout << "3." << time(NULL) << endl;

    // transfer data back to host
    thrust::copy(d_vec.begin(), d_vec.end(), h_vec.begin());
#else
    std::sort(h_vec.begin(), h_vec.end());
#endif

    std::cout << "4." << time(NULL) << endl;
  }catch (thrust::system_error &e){
    std::cerr << "Error accessing vector element: " << e.what() << std::endl;
    exit(-1);
  }
  return 0;
}
