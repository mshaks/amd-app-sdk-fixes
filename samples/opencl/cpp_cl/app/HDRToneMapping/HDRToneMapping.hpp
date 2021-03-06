/* ============================================================

Copyright (c) 2011 Advanced Micro Devices, Inc.  All rights reserved.

Redistribution and use of this material is permitted under the following 
conditions:

Redistributions must retain the above copyright notice and all terms of this 
license.

In no event shall anyone redistributing or accessing or using this material 
commence or participate in any arbitration or legal action relating to this 
material against Advanced Micro Devices, Inc. or any copyright holders or 
contributors. The foregoing shall survive any expiration or termination of 
this license or any agreement or access or use related to this material. 

ANY BREACH OF ANY TERM OF THIS LICENSE SHALL RESULT IN THE IMMEDIATE REVOCATION 
OF ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE THIS MATERIAL.

THIS MATERIAL IS PROVIDED BY ADVANCED MICRO DEVICES, INC. AND ANY COPYRIGHT 
HOLDERS AND CONTRIBUTORS "AS IS" IN ITS CURRENT CONDITION AND WITHOUT ANY 
REPRESENTATIONS, GUARANTEE, OR WARRANTY OF ANY KIND OR IN ANY WAY RELATED TO 
SUPPORT, INDEMNITY, ERROR FREE OR UNINTERRUPTED OPERA TION, OR THAT IT IS FREE 
FROM DEFECTS OR VIRUSES.  ALL OBLIGATIONS ARE HEREBY DISCLAIMED - WHETHER 
EXPRESS, IMPLIED, OR STATUTORY - INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED 
WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
ACCURACY, COMPLETENESS, OPERABILITY, QUALITY OF SERVICE, OR NON-INFRINGEMENT. 
IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, REVENUE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED OR BASED ON ANY THEORY OF LIABILITY 
ARISING IN ANY WAY RELATED TO THIS MATERIAL, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE. THE ENTIRE AND AGGREGATE LIABILITY OF ADVANCED MICRO DEVICES, 
INC. AND ANY COPYRIGHT HOLDERS AND CONTRIBUTORS SHALL NOT EXCEED TEN DOLLARS 
(US $10.00). ANYONE REDISTRIBUTING OR ACCESSING OR USING THIS MATERIAL ACCEPTS 
THIS ALLOCATION OF RISK AND AGREES TO RELEASE ADVANCED MICRO DEVICES, INC. AND 
ANY COPYRIGHT HOLDERS AND CONTRIBUTORS FROM ANY AND ALL LIABILITIES, 
OBLIGATIONS, CLAIMS, OR DEMANDS IN EXCESS OF TEN DOLLARS (US $10.00). THE 
FOREGOING ARE ESSENTIAL TERMS OF THIS LICENSE AND, IF ANY OF THESE TERMS ARE 
CONSTRUED AS UNENFORCEABLE, FAIL IN ESSENTIAL PURPOSE, OR BECOME VOID OR 
DETRIMENTAL TO ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS FOR ANY REASON, THEN ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE 
THIS MATERIAL SHALL TERMINATE IMMEDIATELY. MOREOVER, THE FOREGOING SHALL 
SURVIVE ANY EXPIRATION OR TERMINATION OF THIS LICENSE OR ANY AGREEMENT OR 
ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE IS HEREBY PROVIDED, AND BY REDISTRIBUTING OR ACCESSING OR USING THIS 
MATERIAL SUCH NOTICE IS ACKNOWLEDGED, THAT THIS MATERIAL MAY BE SUBJECT TO 
RESTRICTIONS UNDER THE LAWS AND REGULATIONS OF THE UNITED STATES OR OTHER 
COUNTRIES, WHICH INCLUDE BUT ARE NOT LIMITED TO, U.S. EXPORT CONTROL LAWS SUCH 
AS THE EXPORT ADMINISTRATION REGULATIONS AND NATIONAL SECURITY CONTROLS AS 
DEFINED THEREUNDER, AS WELL AS STATE DEPARTMENT CONTROLS UNDER THE U.S. 
MUNITIONS LIST. THIS MATERIAL MAY NOT BE USED, RELEASED, TRANSFERRED, IMPORTED,
EXPORTED AND/OR RE-EXPORTED IN ANY MANNER PROHIBITED UNDER ANY APPLICABLE LAWS, 
INCLUDING U.S. EXPORT CONTROL LAWS REGARDING SPECIFICALLY DESIGNATED PERSONS, 
COUNTRIES AND NATIONALS OF COUNTRIES SUBJECT TO NATIONAL SECURITY CONTROLS. 
MOREOVER, THE FOREGOING SHALL SURVIVE ANY EXPIRATION OR TERMINATION OF ANY 
LICENSE OR AGREEMENT OR ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE REGARDING THE U.S. GOVERNMENT AND DOD AGENCIES: This material is 
provided with "RESTRICTED RIGHTS" and/or "LIMITED RIGHTS" as applicable to 
computer software and technical data, respectively. Use, duplication, 
distribution or disclosure by the U.S. Government and/or DOD agencies is 
subject to the full extent of restrictions in all applicable regulations, 
including those found at FAR52.227 and DFARS252.227 et seq. and any successor 
regulations thereof. Use of this material by the U.S. Government and/or DOD 
agencies is acknowledgment of the proprietary rights of any copyright holders 
and contributors, including those of Advanced Micro Devices, Inc., as well as 
the provisions of FAR52.227-14 through 23 regarding privately developed and/or 
commercial computer software.

This license forms the entire agreement regarding the subject matter hereof and 
supersedes all proposals and prior discussions and writings between the parties 
with respect thereto. This license does not affect any ownership, rights, title,
or interest in, or relating to, this material. No terms of this license can be 
modified or waived, and no breach of this license can be excused, unless done 
so in a writing signed by all affected parties. Each term of this license is 
separately enforceable. If any term of this license is determined to be or 
becomes unenforceable or illegal, such term shall be reformed to the minimum 
extent necessary in order for this license to remain in effect in accordance 
with its terms as modified by such reformation. This license shall be governed 
by and construed in accordance with the laws of the State of Texas without 
regard to rules on conflicts of law of any state or jurisdiction or the United 
Nations Convention on the International Sale of Goods. All disputes arising out 
of this license shall be subject to the jurisdiction of the federal and state 
courts in Austin, Texas, and all defenses are hereby waived concerning personal 
jurisdiction and venue of these courts.

============================================================ */

#ifndef _HDRTONEMAPPING_HPP__
#define _HDRTONEMAPPING_HPP__

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

/**
* \File HDRToneMapping.hpp
* \brief declaration of the class HDRToneMapping
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDKCommon.hpp>
#include <SDKApplication.hpp>
#include <SDKFile.hpp>
#include <SDKBitMap.hpp>
#include <CL/cl.hpp>

/**
* \class HDRToneMapping
* \brief And HDRToneMaping class. This class is derived from SDKSample base class 
* This class implements tonemapping operation using OpenCL. 
* This operation is used to convert an HDR image to LDR image
* Pattanaik tone mapping operator is used to implement this.
*/

class HDRToneMapping : public SDKSample
{
public: 
    /**
    * \fn HDRToneMapping()
    * \brief A constructor
    * \param sampleName The name of the sample 
    */
    HDRToneMapping(std::string sampleName) : SDKSample(sampleName)
    {
        cPattanaik = 0.25f;
        gammaPattanaik = 0.4f;
        deltaPattanaik = 0.000002f;
        inputImageName = "input.hdr";
        outputImageName = "output.bmp";
        numChannels = 4;
        averageLuminance = 0.0f;
        iterations = 1;
        blockSizeX = 16;
        blockSizeY = 16;
        input = NULL;
        output = NULL;
        referenceOutput = NULL;
    }

    /**
    * \fn HDRToneMapping()
    * \brief A constructor
    * \param sampleName The name of the sample 
    */
    HDRToneMapping(const char* sampleName) : SDKSample(sampleName)
    {
        cPattanaik = 0.25f;
        gammaPattanaik = 0.4f;
        deltaPattanaik = 0.000002f;
        inputImageName = "input.hdr";
        outputImageName = "output.bmp";
        numChannels = 4;
        averageLuminance = 0.0f;
        iterations = 1;
        blockSizeX = 16;
        blockSizeY = 16;
        input = NULL;
        output = NULL;
        referenceOutput = NULL;
    }
    
    /**
    * \fn ~HDRToneMapping()
    * \brief A destructor
    */
    ~HDRToneMapping()
    {
        
    }

    /**
     * \fn int genBinaryImage()
     * \brief Override from SDKSample, Generate binary image of given kernel 
     * and exit application.
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int genBinaryImage();

    /**
    * \fn int setupCL()
    * \brief OpenCL related initialisations. 
    * Set up Context, Device list, Command Queue, Memory buffers
    * Build CL kernel program executable
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int setupCL();

    /**
    * \fn int cpuPattanaikReference();
    * \brief CPU reference implementation of the pattanaik tone mapping operator
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int cpuPattanaikReference();

    /**
    * \fn int runCLKernels()
    * \brief Set values for kernels' arguments, enqueue calls to the kernels
    * on to the command queue, wait till end of kernel execution.
    * Get kernel start and end time if timing is enabled
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int runCLKernels();

    /**
    * \fn void printStats()
    * \brief Override from SDKSample. Print sample stats.
    */
    void printStats();

    /**
    * \fn int initialize()
    * \brief Override from SDKSample. Initialize 
    * command line parser, add custom options
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int initialize();

    /**
    * \fn int setup()
    * \brief Override from SDKSample, adjust width and height 
    * of execution domain, perform all sample setup
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int setup();

    /**
    * \fn int run()
    * \brief Override from SDKSample
    * Run OpenCL Sobel Filter
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int run();

    /**
    * \fn int cleanup()
    * \brief Override from SDKSample
    * Cleanup memory allocations
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int cleanup();

    /**
    * \fn int verifyResults()
    * \brief Override from SDKSample
    * Verify against reference implementation
    * @return SDK_SUCCESS on success and SDK_FAILURE on failure
    */
    int verifyResults();

    /**
    * \fn int readInputImage()
    * \brief Reading the input image 
    */
    int readInputImage();

private:
    std::string inputImageName;                         /**<Name of the input image*/
    std::string outputImageName;                        /**<Name of the output image*/
    cl_float cPattanaik;                                /**<C is a parameter used in Pattanaik tone mapping operator */
    cl_float gammaPattanaik;                            /**<gamma is used in pattanaik tone mapping implementation*/
    cl_float deltaPattanaik;                            /**<Delta is used in pattanaik tone mapping implementation*/
    cl_uint width;                                      /**<Width of the image */
    cl_uint height;                                     /**<Height of the image*/
    cl_uint numChannels;                                /**<Number of channels in the image */
    cl_double setupTime;                                /**< time taken to setup OpenCL resources and building kernel */
    cl_double kernelTime;                               /**< time taken to run kernel and read result back */
    cl_float *input;                                    /**< input data*/
    cl_float *output;                                   /**< output data*/
    cl_float *referenceOutput;                          /**< CPU reference output data */
    cl::Context context;                                /**< Context */
    std::vector<cl::Device> devices;                    /**< vector of devices */
    std::vector<cl::Device> device;                     /**< device to be used */
    std::vector<cl::Platform> platforms;                /**< vector of platforms */
    cl::CommandQueue commandQueue;                      /**< command queue */
    cl::Buffer inputImageBuffer;                        /**< input buffer to device */
    cl::Buffer outputImageBuffer;                       /**< output buffer from device */
    cl::Kernel kernel;                                  /**< Kernel object */
    size_t kernelWorkGroupSize;                         /**< Group Size returned by kernel */
    size_t blockSizeX;                                  /**< Work-group size in x-direction */
    size_t blockSizeY;                                  /**< Work-group size in y-direction */
    cl::Program program;                                /**< program object */
    cl_float averageLuminance;                          /**<Average luminance value of the input image */
    int iterations;                                     /**< Number of iterations for kernel execution */
    size_t       maxWorkGroupSize;                      /**< Device Specific Information */
    cl_uint         maxDimensions;
    size_t *     maxWorkItemSizes;
    cl_ulong     totalLocalMemory;
    streamsdk::SDKDeviceInfo deviceInfo;/**< Structure to store device information*/
    streamsdk::KernelWorkGroupInfo kernelInfo;/**< Structure to store kernel related info */
};

#endif 
