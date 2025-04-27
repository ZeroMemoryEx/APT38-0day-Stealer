# Lazarus-Tactic

<div align="center">
  <img src="https://github.com/ZeroMemoryEx/APT38-0day-Stealer/assets/60795188/ac19ad80-a716-4e3e-b2d8-8e3adbb1b146" alt="Image Description">
</div>

* A program that automates the APT38 technique, which has been utilized to target cybersecurity researchers experts

* Lazarus is a state-sponsored group affiliated with North Korea, has a well-documented track record of targeting cybersecurity researchers. Among their notable techniques, one stands out for its effectiveness in tricking numerous cybersecurity experts.
* The attackers create multiple Twitter and other social media accounts to establish credibility. Through social engineering tactics, they manipulate security researchers into engaging in collaborative research using a Microsoft Visual Studio Project, the project contains a malicious code in the vcxproj file. Consequently, when the researcher attempts to build the project, the malicious code embedded within it is executed.

# technical Details

This analysis is based on information shared by both [Google Threat Analysis Group](https://blog.google/threat-analysis-group/new-campaign-targeting-security-researchers/) and a security researcher [Joel Eriksson](https://x.com/OwariDa/status/1353994626303188993) who documented their experience with this attack. Their tweet highlighted effective protection measures:


## Initial Approach

* Create believable security researcher personas on social platforms and Build trust through technical conversations

![image](https://github.com/user-attachments/assets/0037de85-138d-40fc-9ab6-7f54ea35ae3c)


* Target actual security researchers through direct messages and Offer collaboration on "proof of concept" projects
  
![image](https://github.com/user-attachments/assets/53d7de0f-6c2e-470c-99c5-47ff98e696a1)


## Delivery Mechanism

* Send encrypted ZIP files containing Visual Studio projects and claim the projects demonstrate interesting vulnerabilities
Mention encryption to appear security-conscious

![image](https://github.com/user-attachments/assets/c9f18eb1-2402-4ccb-b0da-f018b35d609a)

Use small file sizes (452.13KB) to seem like legitimate code projects

## Execution Method

Hide malicious PowerShell commands within Visual Studio project files the powerShell commands execute with bypassed execution policy and hidden windows
Include OS checks that verify:

* Windows 10 is running (osversion.version.major -eq 10)
* System is 64-bit (is64bitoperatingsystem)
* A specific path exists (Test-Path x64\Debug\Browse.VC.db)

Key technique: Use rundll32 to load malicious code from a file disguised as a Visual Studio database file and call a specific exported function ENGINE_get_RAND with two parameters: 
A 16-character string that appears to be a key/identifier: 6bt7cJNGEb3Bx9yK
A numeric value: 2907

![image](https://github.com/user-attachments/assets/6043aa38-6c65-4107-89da-71336baf2ec6)


# APT38-0day-Stealer technical Details


* Upon execution within the Visual Studio projects directory, the program infects all vcxproj files by injecting custom code. This code is designed to execute when the individual attempts to build the project .

    ![Screenshot 2023-02-25 180210](https://user-images.githubusercontent.com/60795188/221369862-ef3bd034-66ac-46e1-b2ac-d349a6cf6aa8.png)

# DEMO
   https://user-images.githubusercontent.com/60795188/221441360-f727834f-3759-444c-a8bb-2a8562a433c8.mp4

