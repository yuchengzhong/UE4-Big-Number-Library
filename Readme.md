# Getting Started
## 0.Plugin Info
- This has been tested on UE4.26. It may not work on UE4.27 or UE5, as the editor module may cause conflicts.
- This has not been tested for packaging and may not be compatible with platforms other than Windows.
- This includes exclusive variable pins for blueprint nodes and an exclusive variable properties panel. It is almost identical to the original numerical data type.
- 
## 1.New Types
#### A.Big Int (BI)
BI represents a large integer number.
#### B.Big Decimal (BD)
BD represents a large decimal number.

## 2.Conversion
#### ----Keywords: From / To /Conver

BI and BD can be converted to and from the following types:
- int32
- int64
- float
- double
- FString

#### String Modes

#### Decimal Mode(Dec)
Example decimal strings:

- 1.23456
- -0.2455
- 5125.0 

Note: Only decimal digits up to 9 are valid.

#### ABC Mode
Example ABC strings:
- 1A234(1234)
- 1A234.12345(1234.12345)
- 1Z234B123A523 

In ABC mode, the letters A, B, C, etc. are used to represent thousand, million, billion, and so on (up to Z).