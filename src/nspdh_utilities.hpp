#ifndef _NSPDH_UTIL_ 
#define _NSPDH_UTIL_

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <vector>
#include "portable_mutex.hpp"

namespace nspdh 
{
    // Included as a workaround for Unix/Windows compatibility.
    #if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #else
    #include <unistd.h>
    void Sleep(int x);
    #endif

    // This is included as a workaround for older versions of g++.
    #ifndef nullptr 
    #define nullptr NULL
    #endif

    using boost::multiprecision::cpp_int;

    // Define the types of generators. //
    typedef boost::random::independent_bits_engine<boost::random::mt19937, 8192*2, cpp_int> generator_type;
    typedef boost::random::independent_bits_engine<boost::random::mt19937, 256, cpp_int> generator_type2; // Using a smaller generator here in hopes of speeding up the Miller-Rabin Primality test.

    #define NSPDH_TRIAL_DIVISIONS 40000

    #define NSPDH_SEARCH 0
    #define NSPDH_POHLIG_FOUND  1
    #define NSPDH_MODULUS_FOUND 2
    #define NSPDH_FREEZE 3
    #define NSPDH_DHPARAM (1<<2)
    #define NSPDH_DSAPARAM (2<<2)
    
    using namespace boost::math;
    
    // Defines the available functions
    int blog2(cpp_int val);
    bool isprime(long long x);
    long long prime(int x);
    char fastPrimeC(const cpp_int& v, long long *cache = nullptr, long long by = 0);
    std::vector<int> factor(int val);
    char checkGenerator(const cpp_int& proposed, const cpp_int& modPrime, const cpp_int& phPrime, int smallVal);
    char checkGeneratorInclusive(const cpp_int& proposed, const cpp_int& modPrime, const cpp_int& phPrime, int smallVal);
    cpp_int numberOfGenerators(const cpp_int& modPrime, const cpp_int& phPrime, int smallVal);
    cpp_int generatePrime(int size, volatile char* completionStatus);
    cpp_int generatePrimeTuple(int size, cpp_int base, volatile char* completionStatus);
}
#endif