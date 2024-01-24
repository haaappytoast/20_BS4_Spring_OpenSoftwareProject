# 20_BS4_Spring_OpenSoftwareProject
The purpose of this project is 
1. To explore about introductory theories in image processing, which serves as a basic unit for studying computer vision.
2. It also introduces fundaments of deep neural networks and its application to computer vision.

Briefly speaking, I implemented codes of 
~~~
- Rotating, stitching of images
- Showing histogram of images
- Filters of images, specifically, gray filter, uniform mean filter, gaussian filter, sobel filter, laplacian filter, and unsharpMasking filter
- Salt and pepper noise, gaussian noise removals using median filter, mean filter, gaussian filters and etc.
- Edge/corner detection
- SIFT
- Affine/Hough transformation
~~~
For more details, please refer to technical report PDF in each section.


# 1. Requirments
#### HW1 - 7: Code is written in C++ and uses Visual Studio 2019 for framework 
This project requires:
* Visual Studio Community
  * Version: 2019
* Library
  * OpenCV 2.4.0
    * tutorial pdf: [OSP-Lec01-OpenCV_tutorial_for2.4.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205452/OSP-Lec01-OpenCV_tutorial_for2.4.pdf)

#### HW8 - 10: Code is written in Python and I left google drive share link b/c of storage issues
----------

# 2. Introduction
## 2-1. Rotating & Stitching (HW1)

### Results

**Rotation using interpolation method of bilinear (left) and nearest (right)**

<image src = "https://user-images.githubusercontent.com/45995611/216963458-ca5ccdb5-7094-4187-92de-4b30a0fd5a2c.png" width="30%" height="30%"></left>
<image src = "https://user-images.githubusercontent.com/45995611/216963894-099785e7-5ff0-4ed2-8463-04d7ba38aad9.png" width="30%" height="30%"></right>

**Stitching using inverse warping**

<image src = "https://user-images.githubusercontent.com/45995611/216965144-7666dd3d-a0bd-4141-bbab-68ad10340dc8.png" width="50%" height="50%"></right>

> **ETC**
>* HW introduction: look at p.41 - 43 in pdf for more information : [Rotating.Stitching.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205467/Rotating.Stitching.pdf)
>* LECTURE NOTES
>  * [OSP-Lec00-Introduction.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205471/OSP-Lec00-Introduction.pdf)
>  * [OSP-Lec01-Fundamentals.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205472/OSP-Lec01-Fundamentals.pdf)
>  * [OSP-Lec02-Display.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205469/OSP-Lec02-Display.pdf)
>  * [OSP-Lec02-Display-Lab.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205468/OSP-Lec02-Display-Lab.pdf)

<br/><br/>


## 2-2. Histogram (HW2)

### Results

**Input image, grayscal image, and corresponding histograms**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/ab99b045-e9b2-49b1-9ab1-9f937b89d95c" width="50%" height="50%"></left>

>**ETC**
>* HW introduction: look at p.34 - 44 in LECTURE NOTE pdf for more information
>* LECTURE NOTES
>  * [OSP-Lec03-Pixel.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205532/OSP-Lec03-Pixel.pdf)
  

  <br/><br/>

## 2-3. Filters (HW3)

### Results

**Mean Filter: according to filter size**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/abf89ac7-3ab7-4e54-80e1-0ff8dea0a1de" width="50%" height="50%"></left>

**Gaussian Filter: according to filter size**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/b9c5aff5-727f-4526-811f-966bec32db12" width="50%" height="50%"></left>


**Sobel Filter: grayscale and RGB image**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/72570ac6-4f4e-4d6b-83bd-6bf5ed844f01" width="50%" height="50%"></left>

>**ETC**
>* HW introduction: look at p.34 - 38 in LECTURE NOTE pdf for more information
>* LECTURE NOTES
>  * [OSP-Lec04-Region.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205566/OSP-Lec04-Region.pdf)


<br/><br/>

## 2-4. Noise Removal & Segmentation (HW4)
* Segmentation 프로그램 사용결과: [Mean shift segmentation(프로그램 사용결과).pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205593/Mean.shift.segmentation.pdf)
### Results

**Salt and Pepper Noise Removal: using Mean Filter**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/ebb46495-acae-45b0-8e2b-412df1fb92b5" width="70%" height="70%"></left>

### Results

**Gaussian Noise Removal: using Gaussian Filter**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/66685efc-bc8c-4d87-80fe-72663deb6bcc" width="40%" height="40%"></left>


>**ETC**
>* HW introduction
>  * look at p.27-31 in LECTURE NOTE [OSP-Lec05] pdf for more information (Noise Removal)
>  * look at p.51-53 in LECTURE NOTE [OSP-Lec06] pdf for more information (Segmentation)

>* LECTURE NOTES
>  * [OSP-Lec05-Restoration.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205600/OSP-Lec05-Restoration.pdf)
>  * [OSP-Lec06-Segmentation.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205603/OSP-Lec06-Segmentation.pdf)


## 2-5. Edge/Corner Detection (HW5)

### Results

**Noise가 섞인 이미지를 Gaussian Filter를 적용한 후, Laplacian filter 적용**

**Analysis**
* Gaussian filter의 sigma를 높여주었을 때의 효과에 대해 살펴보았다. sigma가 커졌다는 것은 옆 주변의 pixel 값들을 많이 죽이지 않는다는 뜻이다( blurring이 덜 됨) 따라서 그림4와 마찬가지로
짜잘짜잘한 노이즈들이 남아서 edge로 detect된 것을 확인할 수 있었다. (빨간색 동그라미 친 곳)

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/412e6c7e-9dc2-4e5a-8028-8c0e6b17ea2b" width="100%" height="100%"></left>


>**ETC**
>* HW introduction: look at p.40-42 in LECTURE NOTE pdf for more information
>* LECTURE NOTES
>  * [OSP-Lec07-Edge_Corner.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205629/OSP-Lec07-Edge_Corner.pdf)

## 2-6. HW6 - SIFT (HW6)
### Results

**Input images, I1 and I2 (left) and keypoint matching results (right)**

<image src = "https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/assets/45995611/7e7e15a3-70b2-4252-a2c4-ce37119bc908" width="100%" height="100%"></left>

>* HW introduction: look at p.27-28 in LECTURE NOTE pdf for more information
>* LECTURE NOTES
>  * [OSP-Lec08-Descriptor.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205649/OSP-Lec08-Descriptor.pdf)

<br/><br/>

## 2-7. HW7 - Affine/Hough Transformation

> **ETC**
> * HW introduction: look at p.28-31 in LECTURE NOTE pdf for more information
>* LECTURE NOTES
>  * [OSP-Lec09-Fitting.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205674/OSP-Lec09-Fitting.pdf)


----------
## [Source Code Google Drive Link] 
* Since files are too large to upload in github, I will share google drive link if you request

## 2-8. HW8 - Multi Layer Perceptron

### [Source Code Google Drive Link] 
* Since files are too large to upload in github, I will share google drive link if you request

  
> **ETC**
>* HW introduction: look at LECTURE NOTE [OSP-Lec12-Backpropagation_MLP_practice.pdf] pdf for more information (especially p.14~16)
>* LECTURE NOTES
>  * [OSP-Lec11-Loss function.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205718/OSP-Lec11-Loss.function.pdf)
>  * [OSP-Lec10-Deep learning_Intro.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205716/OSP-Lec10-Deep.learning_Intro.pdf)
>  * [OSP-Lec12-Backpropagation_MLP.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205717/OSP-Lec12-Backpropagation_MLP.pdf)
>  * [OSP-Lec12-Backpropagation_MLP_practice.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205715/OSP-Lec12-Backpropagation_MLP_practice.pdf)


## 2-9. HW9 - CNN


### [Source Code Google Drive Link] 
* Since files are too large to upload in github, I will share google drive link if you request

> **ETC**
>* HW introduction: look at LECTURE NOTE [OSP-Lec14-CNN architecture-practice-v2.pdf] pdf for more information (especially p.22~31)
>* LECTURE NOTES
>  * [OSP-Lec13-CNN.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205744/OSP-Lec13-CNN.pdf)
>  * [OSP-Lec14-CNN architecture.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205742/OSP-Lec14-CNN.architecture.pdf)
>  * [OSP-Lec14-CNN architecture-practice-v2.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205743/OSP-Lec14-CNN.architecture-practice-v2.pdf)

## 2-10. HW10 - Encoder & Decoder


### [Source Code Google Drive Link] 
* Since files are too large to upload in github, I will share google drive link if you request


> **ETC**
>* HW introduction: look at LECTURE NOTE [OSP-Lec15-Encoder_Decoder-practice-v2.pdf] pdf for more information (especially p.5~11)
>* LECTURE NOTES
>  * [OSP-More on deep learning.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205855/OSP-More.on.deep.learning.pdf)
>  * [OSP-Lec15-Encoder_Decoder.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205856/OSP-Lec15-Encoder_Decoder.pdf)
>  * [OSP-Lec15-Encoder_Decoder-practice-v2.pdf](https://github.com/haaappytoast/20_BS4_Spring_OpenSoftwareProject/files/9205865/OSP-Lec15-Encoder_Decoder-practice-v2.pdf)


