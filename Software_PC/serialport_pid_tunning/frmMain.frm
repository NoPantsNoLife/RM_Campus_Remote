VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.2#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmMain 
   Caption         =   "Pid Tunning"
   ClientHeight    =   9132
   ClientLeft      =   48
   ClientTop       =   396
   ClientWidth     =   8100
   LinkTopic       =   "Form1"
   ScaleHeight     =   9132
   ScaleWidth      =   8100
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   6480
      Top             =   360
   End
   Begin VB.TextBox txtBaud 
      Height          =   372
      Left            =   1080
      TabIndex        =   8
      Text            =   "115200"
      Top             =   600
      Width           =   852
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Open"
      BeginProperty Font 
         Name            =   "ËÎÌå"
         Size            =   15
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   732
      Left            =   2880
      TabIndex        =   7
      Top             =   240
      Width           =   1572
   End
   Begin MSCommLib.MSComm com 
      Left            =   4920
      Top             =   240
      _ExtentX        =   974
      _ExtentY        =   974
      _Version        =   393216
      CommPort        =   4
      DTREnable       =   0   'False
      RThreshold      =   1
      BaudRate        =   115200
      InputMode       =   1
   End
   Begin VB.TextBox txtPort 
      Height          =   372
      Left            =   1080
      TabIndex        =   6
      Text            =   "4"
      Top             =   120
      Width           =   1692
   End
   Begin MSComctlLib.Slider sldP 
      Height          =   372
      Left            =   1560
      TabIndex        =   0
      Top             =   1200
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldI 
      Height          =   372
      Left            =   1560
      TabIndex        =   4
      Top             =   1800
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldD 
      Height          =   372
      Left            =   1560
      TabIndex        =   5
      Top             =   2400
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldPx 
      Height          =   372
      Left            =   1560
      TabIndex        =   11
      Top             =   3240
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldIx 
      Height          =   372
      Left            =   1560
      TabIndex        =   12
      Top             =   3840
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldDx 
      Height          =   372
      Left            =   1560
      TabIndex        =   13
      Top             =   4440
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldPy 
      Height          =   372
      Left            =   1560
      TabIndex        =   17
      Top             =   7320
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldIy 
      Height          =   372
      Left            =   1560
      TabIndex        =   18
      Top             =   7920
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldDy 
      Height          =   372
      Left            =   1560
      TabIndex        =   19
      Top             =   8520
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldPr 
      Height          =   372
      Left            =   1560
      TabIndex        =   23
      Top             =   5280
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldIr 
      Height          =   372
      Left            =   1560
      TabIndex        =   24
      Top             =   5880
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin MSComctlLib.Slider sldDr 
      Height          =   372
      Left            =   1560
      TabIndex        =   25
      Top             =   6480
      Width           =   5772
      _ExtentX        =   10181
      _ExtentY        =   656
      _Version        =   393216
      Min             =   1
      Max             =   500
      SelStart        =   10
      Value           =   10
   End
   Begin VB.Label lblPr 
      Caption         =   "kPr = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   28
      Top             =   5280
      Width           =   972
   End
   Begin VB.Label lblIr 
      Caption         =   "kIr = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   27
      Top             =   6000
      Width           =   972
   End
   Begin VB.Label lblDr 
      Caption         =   "kDr = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   26
      Top             =   6600
      Width           =   972
   End
   Begin VB.Label lblPy 
      Caption         =   "kPy = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   22
      Top             =   7320
      Width           =   972
   End
   Begin VB.Label lblIy 
      Caption         =   "kIy = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   21
      Top             =   8040
      Width           =   972
   End
   Begin VB.Label lblDy 
      Caption         =   "kDy = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   20
      Top             =   8640
      Width           =   972
   End
   Begin VB.Label lblPx 
      Caption         =   "kPx = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   16
      Top             =   3240
      Width           =   972
   End
   Begin VB.Label lblIx 
      Caption         =   "kIx = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   15
      Top             =   3960
      Width           =   972
   End
   Begin VB.Label lblDx 
      Caption         =   "kDx = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   14
      Top             =   4560
      Width           =   972
   End
   Begin VB.Label Label5 
      Height          =   852
      Left            =   4800
      TabIndex        =   10
      Top             =   120
      Width           =   3132
   End
   Begin VB.Label Label4 
      Caption         =   "COM"
      Height          =   252
      Left            =   600
      TabIndex        =   9
      Top             =   240
      Width           =   492
   End
   Begin VB.Label lblD 
      Caption         =   "kD = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   3
      Top             =   2520
      Width           =   972
   End
   Begin VB.Label lblI 
      Caption         =   "kI = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   2
      Top             =   1920
      Width           =   972
   End
   Begin VB.Label lblP 
      Caption         =   "kP = 1.0"
      Height          =   252
      Left            =   480
      TabIndex        =   1
      Top             =   1200
      Width           =   972
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim data(23) As Byte

Private Sub com_OnComm()
    Select Case com.CommEvent
        Case comEvReceive
            Label5.Caption = StrConv(com.Input, vbUnicode)
            com.InBufferCount = 0
    End Select
End Sub

Private Sub Command1_Click()
On Error Resume Next
    If com.PortOpen = False Then
        com.PortOpen = True
        If com.PortOpen = True Then
            Timer1.Enabled = True
            Command1.Caption = "Close"
        End If
    Else
        com.PortOpen = False
        Timer1.Enabled = False
        Command1.Caption = "Open"
    End If
End Sub

Private Sub Label1_Click()

End Sub

Private Sub Label2_Click()

End Sub

Private Sub Form_Load()
    data(0) = 1
    data(2) = 1
    data(4) = 1
    data(6) = 1
    data(8) = 1
    data(10) = 1
    data(12) = 1
    data(14) = 1
    data(16) = 1
    data(18) = 1
    data(20) = 1
    data(22) = 1
End Sub

Private Sub Label3_Click()

End Sub

Private Sub Label7_Click()

End Sub

Private Sub Label9_Click()

End Sub


Private Sub sldP_Scroll()
    lblP = "kP = " & Format(sldP.Value / 10, "0.0")
    data(0) = Int(sldP.Value / 10)
    data(1) = Int(sldP.Value Mod 10)
End Sub

Private Sub sldPx_scroll()
    lblPx = "kPx = " & Format(sldPx.Value / 10, "0.0")
    data(6) = Int(sldPx.Value / 10)
    data(7) = Int(sldPx.Value Mod 10)
End Sub

Private Sub sldPy_scroll()
    lblPy = "kPy = " & Format(sldPy.Value / 10, "0.0")
    data(12) = Int(sldPy.Value / 10)
    data(13) = Int(sldPy.Value Mod 10)
End Sub

Private Sub sldPr_scroll()
    lblPr = "kPr = " & Format(sldPr.Value / 10, "0.0")
    data(18) = Int(sldPr.Value / 10)
    data(19) = Int(sldPr.Value Mod 10)
End Sub

Private Sub sldI_Scroll()
    lblI = "kI = " & Format(sldI.Value / 10, "0.0")
    data(2) = Int(sldI.Value / 10)
    data(3) = Int(sldI.Value Mod 10)
End Sub

Private Sub sldIx_scroll()
    lblIx = "kIx = " & Format(sldIx.Value / 10, "0.0")
    data(8) = Int(sldIx.Value / 10)
    data(9) = Int(sldIx.Value Mod 10)
End Sub

Private Sub sldIy_scroll()
    lblIy = "kIy = " & Format(sldIy.Value / 10, "0.0")
    data(14) = Int(sldIy.Value / 10)
    data(15) = Int(sldIy.Value Mod 10)
End Sub

Private Sub sldIr_scroll()
    lblIr = "kIr = " & Format(sldIr.Value / 10, "0.0")
    data(20) = Int(sldIr.Value / 10)
    data(21) = Int(sldIr.Value Mod 10)
End Sub

Private Sub sldD_Scroll()
    lblD = "kD = " & Format(sldD.Value / 10, "0.0")
    data(4) = Int(sldD.Value / 10)
    data(5) = Int(sldD.Value Mod 10)
End Sub

Private Sub sldDx_scroll()
    lblDx = "kDx = " & Format(sldDx.Value / 10, "0.0")
    data(10) = Int(sldDx.Value / 10)
    data(11) = Int(sldDx.Value Mod 10)
End Sub

Private Sub sldDy_scroll()
    lblDy = "kDy = " & Format(sldDy.Value / 10, "0.0")
    data(16) = Int(sldDy.Value / 10)
    data(17) = Int(sldDy.Value Mod 10)
End Sub

Private Sub sldDr_scroll()
    lblDr = "kDr = " & Format(sldDr.Value / 10, "0.0")
    data(22) = Int(sldDr.Value / 10)
    data(23) = Int(sldDr.Value Mod 10)
End Sub

Private Sub Timer1_Timer()
On Error Resume Next
    DoEvents
    com.Output = data
End Sub

Private Sub txtBaud_Change()
On Error Resume Next
    com.Settings = txtBaud.Text & ",n,8,1"
End Sub

Private Sub txtPort_Change()
On Error Resume Next
    com.CommPort = txtPort.Text
End Sub
