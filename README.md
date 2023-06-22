# Lazarus-Tactic

<div align="center">
  <img src="https://github.com/ZeroMemoryEx/APT38-0day-Stealer/assets/60795188/ac19ad80-a716-4e3e-b2d8-8e3adbb1b146" alt="Image Description">
</div>

* A program that automates the APT38 technique, which has been utilized to target cybersecurity researchers experts

* Lazarus is a state-sponsored group affiliated with North Korea, has a well-documented track record of targeting cybersecurity researchers. Among their notable techniques, one stands out for its effectiveness in tricking numerous cybersecurity experts.
* The attackers create multiple Twitter and other social media accounts to establish credibility. Through social engineering tactics, they manipulate security researchers into engaging in collaborative research using a Microsoft Visual Studio Project, the project contains a malicious code in the vcxproj file. Consequently, when the researcher attempts to build the project, the malicious code embedded within it is executed.

# technical Details

* Upon execution within the Visual Studio projects directory, the program infects all vcxproj files by injecting custom code. This code is designed to execute when the individual attempts to build the project .

    ![Screenshot 2023-02-25 180210](https://user-images.githubusercontent.com/60795188/221369862-ef3bd034-66ac-46e1-b2ac-d349a6cf6aa8.png)

# DEMO
   https://user-images.githubusercontent.com/60795188/221441360-f727834f-3759-444c-a8bb-2a8562a433c8.mp4

