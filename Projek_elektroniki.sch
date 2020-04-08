EESchema Schematic File Version 4
LIBS:Projek_elektroniki-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Manipulator MRRR"
Date "08.04.2020"
Rev ""
Comp "Patryk Szelewski"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Motor:Motor_Servo M1
U 1 1 5E8DE189
P 9050 4950
F 0 "M1" H 9382 5015 50  0000 L CNN
F 1 "Motor Servo PowerHD HD-6001HB-standard" H 9382 4924 50  0000 L CNN
F 2 "" H 9050 4760 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 9050 4760 50  0001 C CNN
	1    9050 4950
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M2
U 1 1 5E8DEF96
P 9050 5450
F 0 "M2" H 9382 5515 50  0000 L CNN
F 1 "Motor Servo PowerHD HD-6001HB-standard" H 9382 5424 50  0000 L CNN
F 2 "" H 9050 5260 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 9050 5260 50  0001 C CNN
	1    9050 5450
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M3
U 1 1 5E8DFFD6
P 9050 5950
F 0 "M3" H 9382 6015 50  0000 L CNN
F 1 "Motor Servo PowerHD HD-6001HB-standard" H 9382 5924 50  0000 L CNN
F 2 "" H 9050 5760 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 9050 5760 50  0001 C CNN
	1    9050 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder SW2
U 1 1 5E8E1A1C
P 10050 3650
F 0 "SW2" H 10280 3696 50  0000 L CNN
F 1 "Rotary_Encoder_EC16" H 10280 3605 50  0000 L CNN
F 2 "" H 9900 3810 50  0001 C CNN
F 3 "~" H 10050 3910 50  0001 C CNN
	1    10050 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E91034C
P 8550 2550
F 0 "R3" H 8480 2504 50  0000 R CNN
F 1 "10k0Ω" H 8480 2595 50  0000 R CNN
F 2 "" V 8480 2550 50  0001 C CNN
F 3 "~" H 8550 2550 50  0001 C CNN
	1    8550 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:Rotary_Encoder SW1
U 1 1 5E8E2B49
P 10050 3100
F 0 "SW1" H 10280 3146 50  0000 L CNN
F 1 "Rotary_Encoder_EC16" H 10280 3055 50  0000 L CNN
F 2 "Enkoder" H 9900 3260 50  0001 C CNN
F 3 "~" H 10050 3360 50  0001 C CNN
	1    10050 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5E8EA51E
P 9300 2550
F 0 "R5" H 9230 2504 50  0000 R CNN
F 1 "10kΩ" H 9230 2595 50  0000 R CNN
F 2 "" V 9230 2550 50  0001 C CNN
F 3 "~" H 9300 2550 50  0001 C CNN
	1    9300 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5E9108BE
P 8150 2550
F 0 "R2" H 8220 2596 50  0000 L CNN
F 1 "10k0Ω" H 8220 2505 50  0000 L CNN
F 2 "" V 8080 2550 50  0001 C CNN
F 3 "~" H 8150 2550 50  0001 C CNN
	1    8150 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E90FAD3
P 8950 2550
F 0 "R4" H 9020 2596 50  0000 L CNN
F 1 "10kΩ" H 9020 2505 50  0000 L CNN
F 2 "" V 8880 2550 50  0001 C CNN
F 3 "~" H 8950 2550 50  0001 C CNN
	1    8950 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5E9258B6
P 9650 2550
F 0 "R6" H 9720 2596 50  0000 L CNN
F 1 "10k0Ω" H 9720 2505 50  0000 L CNN
F 2 "" V 9580 2550 50  0001 C CNN
F 3 "~" H 9650 2550 50  0001 C CNN
	1    9650 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E926444
P 7750 2550
F 0 "R1" H 7820 2596 50  0000 L CNN
F 1 "10k0Ω" H 7820 2505 50  0000 L CNN
F 2 "" V 7680 2550 50  0001 C CNN
F 3 "~" H 7750 2550 50  0001 C CNN
	1    7750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 3000 9650 3000
Wire Wire Line
	9650 3000 9650 2700
Wire Wire Line
	9750 3200 9300 3200
Wire Wire Line
	9300 3200 9300 2700
Wire Wire Line
	9750 3550 8950 3550
Wire Wire Line
	8950 3550 8950 2700
Wire Wire Line
	9750 3750 8550 3750
Wire Wire Line
	8550 3750 8550 2700
Wire Wire Line
	9750 4150 8150 4150
Wire Wire Line
	8150 4150 8150 2700
Wire Wire Line
	9750 4350 7750 4350
Wire Wire Line
	7750 4350 7750 2700
Text GLabel 9600 3000 0    50   Input ~ 0
SW1_A
Wire Wire Line
	9600 3000 9650 3000
Connection ~ 9650 3000
Wire Wire Line
	9250 3200 9300 3200
Connection ~ 9300 3200
$Comp
L power:+5V #PWR04
U 1 1 5E8E939E
P 8750 2200
F 0 "#PWR04" H 8750 2050 50  0001 C CNN
F 1 "+5V" H 8765 2373 50  0000 C CNN
F 2 "" H 8750 2200 50  0001 C CNN
F 3 "" H 8750 2200 50  0001 C CNN
	1    8750 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2400 7750 2200
Wire Wire Line
	7750 2200 8150 2200
Wire Wire Line
	9650 2400 9650 2200
Wire Wire Line
	9650 2200 9300 2200
Connection ~ 8750 2200
Wire Wire Line
	8150 2400 8150 2200
Connection ~ 8150 2200
Wire Wire Line
	8150 2200 8550 2200
Wire Wire Line
	8550 2400 8550 2200
Connection ~ 8550 2200
Wire Wire Line
	8550 2200 8750 2200
Wire Wire Line
	8950 2400 8950 2200
Connection ~ 8950 2200
Wire Wire Line
	8950 2200 8750 2200
Wire Wire Line
	9300 2400 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	9300 2200 8950 2200
Wire Wire Line
	8850 3550 8950 3550
Connection ~ 8950 3550
Text GLabel 9250 3200 0    50   Input ~ 0
SW_1B
Text GLabel 8850 3550 0    50   Input ~ 0
SW2_A
Text GLabel 8450 3750 0    50   Input ~ 0
SW2_B
Wire Wire Line
	8450 3750 8550 3750
Connection ~ 8550 3750
Text GLabel 8050 4150 0    50   Input ~ 0
SW3_A
Wire Wire Line
	8150 4150 8050 4150
Connection ~ 8150 4150
Text GLabel 8500 4850 0    50   Input ~ 0
M1_PWM
Text GLabel 8500 5350 0    50   Input ~ 0
M2_PWM
Text GLabel 8500 5850 0    50   Input ~ 0
M3_PWM
Wire Wire Line
	8500 4850 8750 4850
Text GLabel 6950 2950 2    50   Input ~ 0
M1_PWM
Text GLabel 6950 3950 2    50   Input ~ 0
M2_PWM
Text GLabel 6950 4050 2    50   Input ~ 0
M3_PWM
$Comp
L power:+5V #PWR01
U 1 1 5E9039FA
P 8050 4950
F 0 "#PWR01" H 8050 4800 50  0001 C CNN
F 1 "+5V" H 8065 5123 50  0000 C CNN
F 2 "" H 8050 4950 50  0001 C CNN
F 3 "" H 8050 4950 50  0001 C CNN
	1    8050 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5E905BFC
P 8750 5050
F 0 "#PWR05" H 8750 4800 50  0001 C CNN
F 1 "GND" H 8755 4877 50  0000 C CNN
F 2 "" H 8750 5050 50  0001 C CNN
F 3 "" H 8750 5050 50  0001 C CNN
	1    8750 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4950 8750 4950
$Comp
L power:+5V #PWR02
U 1 1 5E90808F
P 8050 5450
F 0 "#PWR02" H 8050 5300 50  0001 C CNN
F 1 "+5V" H 8065 5623 50  0000 C CNN
F 2 "" H 8050 5450 50  0001 C CNN
F 3 "" H 8050 5450 50  0001 C CNN
	1    8050 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E90BB6A
P 8750 5550
F 0 "#PWR06" H 8750 5300 50  0001 C CNN
F 1 "GND" H 8755 5377 50  0000 C CNN
F 2 "" H 8750 5550 50  0001 C CNN
F 3 "" H 8750 5550 50  0001 C CNN
	1    8750 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 5450 8750 5450
Wire Wire Line
	8500 5350 8750 5350
Wire Wire Line
	8500 5850 8750 5850
$Comp
L power:+5V #PWR03
U 1 1 5E913BC3
P 8050 5950
F 0 "#PWR03" H 8050 5800 50  0001 C CNN
F 1 "+5V" H 8065 6123 50  0000 C CNN
F 2 "" H 8050 5950 50  0001 C CNN
F 3 "" H 8050 5950 50  0001 C CNN
	1    8050 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 5950 8750 5950
$Comp
L power:GND #PWR07
U 1 1 5E9150E4
P 8750 6050
F 0 "#PWR07" H 8750 5800 50  0001 C CNN
F 1 "GND" H 8755 5877 50  0000 C CNN
F 2 "" H 8750 6050 50  0001 C CNN
F 3 "" H 8750 6050 50  0001 C CNN
	1    8750 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5E9171DD
P 9750 3650
F 0 "#PWR09" H 9750 3400 50  0001 C CNN
F 1 "GND" V 9755 3522 50  0000 R CNN
F 2 "" H 9750 3650 50  0001 C CNN
F 3 "" H 9750 3650 50  0001 C CNN
	1    9750 3650
	0    1    1    0   
$EndComp
$Comp
L Device:Rotary_Encoder SW3
U 1 1 5E8E0E0E
P 10050 4250
F 0 "SW3" H 10280 4296 50  0000 L CNN
F 1 "Rotary_Encoder_EC16" H 10280 4205 50  0000 L CNN
F 2 "" H 9900 4410 50  0001 C CNN
F 3 "~" H 10050 4510 50  0001 C CNN
	1    10050 4250
	1    0    0    -1  
$EndComp
Text GLabel 6950 5350 2    50   Input ~ 0
SW3_A
Text GLabel 6950 5250 2    50   Input ~ 0
SW3_B
Text GLabel 3850 4650 0    50   Input ~ 0
SW1_B
Text GLabel 3850 4550 0    50   Input ~ 0
SW2_A
Text GLabel 3850 4450 0    50   Input ~ 0
SW2_B
$Comp
L power:GND #PWR010
U 1 1 5E918A1E
P 9750 4250
F 0 "#PWR010" H 9750 4000 50  0001 C CNN
F 1 "GND" V 9755 4122 50  0000 R CNN
F 2 "" H 9750 4250 50  0001 C CNN
F 3 "" H 9750 4250 50  0001 C CNN
	1    9750 4250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E91ACAB
P 9750 3100
F 0 "#PWR08" H 9750 2850 50  0001 C CNN
F 1 "GND" V 9755 2972 50  0000 R CNN
F 2 "" H 9750 3100 50  0001 C CNN
F 3 "" H 9750 3100 50  0001 C CNN
	1    9750 3100
	0    1    1    0   
$EndComp
Text GLabel 3850 4750 0    50   Input ~ 0
SW1_A
$Comp
L MCU_Module:NUCLEO64-F411RE U1
U 1 1 5E9548E6
P 5450 3750
F 0 "U1" H 5450 5931 50  0000 C CNN
F 1 "NUCLEO64-F411RE" H 5450 5840 50  0000 C CNN
F 2 "Module:ST_Morpho_Connector_144_STLink" H 6000 1850 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/data_brief/DM00105918.pdf" H 4550 2350 50  0001 C CNN
	1    5450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2950 6550 2950
Wire Wire Line
	6950 3950 6550 3950
Wire Wire Line
	6950 4050 6550 4050
Wire Wire Line
	6950 5250 6550 5250
Wire Wire Line
	6950 5350 6550 5350
Wire Wire Line
	3850 4450 4350 4450
Wire Wire Line
	3850 4550 4350 4550
Wire Wire Line
	3850 4650 4350 4650
Wire Wire Line
	3850 4750 4350 4750
$Comp
L power:+5V #PWR?
U 1 1 5E971A77
P 5250 1550
F 0 "#PWR?" H 5250 1400 50  0001 C CNN
F 1 "+5V" H 5265 1723 50  0000 C CNN
F 2 "" H 5250 1550 50  0001 C CNN
F 3 "" H 5250 1550 50  0001 C CNN
	1    5250 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1550 5250 1750
Wire Wire Line
	4850 5750 4950 5750
Connection ~ 4950 5750
Wire Wire Line
	4950 5750 5050 5750
Connection ~ 5050 5750
Wire Wire Line
	5050 5750 5150 5750
Connection ~ 5150 5750
Wire Wire Line
	5150 5750 5250 5750
Connection ~ 5250 5750
Wire Wire Line
	5250 5750 5350 5750
Connection ~ 5350 5750
Wire Wire Line
	5350 5750 5450 5750
Connection ~ 5450 5750
Wire Wire Line
	5450 5750 5550 5750
Connection ~ 5550 5750
Wire Wire Line
	5550 5750 5650 5750
Connection ~ 5650 5750
Wire Wire Line
	5650 5750 5750 5750
$Comp
L power:GND #PWR?
U 1 1 5E975A4A
P 5350 5900
F 0 "#PWR?" H 5350 5650 50  0001 C CNN
F 1 "GND" H 5355 5727 50  0000 C CNN
F 2 "" H 5350 5900 50  0001 C CNN
F 3 "" H 5350 5900 50  0001 C CNN
	1    5350 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5750 5350 5900
Text GLabel 7650 4350 0    50   Input ~ 0
SW3_B
Wire Wire Line
	7650 4350 7750 4350
Connection ~ 7750 4350
$EndSCHEMATC
