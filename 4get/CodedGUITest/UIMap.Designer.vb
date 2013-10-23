﻿'------------------------------------------------------------------------------
'  <auto-generated>
'      This code was generated by coded UI test builder.
'      Version: 11.0.0.0
'
'      Changes to this file may cause incorrect behavior and will be lost if
'      the code is regenerated.
'  </auto-generated>
' ------------------------------------------------------------------------------

Imports System
Imports System.CodeDom.Compiler
Imports System.Collections.Generic
Imports System.Drawing
Imports System.Text.RegularExpressions
Imports System.Windows.Input
Imports Microsoft.VisualStudio.TestTools.UITest.Extension
Imports Microsoft.VisualStudio.TestTools.UITesting
Imports Microsoft.VisualStudio.TestTools.UITesting.WinControls
Imports Microsoft.VisualStudio.TestTools.UnitTesting
Imports Keyboard = Microsoft.VisualStudio.TestTools.UITesting.Keyboard
Imports Mouse = Microsoft.VisualStudio.TestTools.UITesting.Mouse
Imports MouseButtons = System.Windows.Forms.MouseButtons

Namespace CodedGUITest
    
    <GeneratedCode("Coded UITest Builder", "11.0.60315.1")>  _
    Partial Public Class UIMap
        
        '''<summary>
        '''add a timed task
        '''</summary>
        Public Sub TestAddTimedTask()
            Dim uITextboxInputEdit As WinEdit = Me.UIItem4getWindow.UIEnterCommandHereWindow.UITextboxInputEdit

            'Type 'add tuition ,at crown centre ,from 1900 ,to 2100 ,!' in 'textboxInput' text box
            uITextboxInputEdit.Text = Me.TestAddTimedTaskParams.UITextboxInputEditText

            'Type '{Enter}' in 'textboxInput' text box
            Keyboard.SendKeys(uITextboxInputEdit, Me.TestAddTimedTaskParams.UITextboxInputEditSendKeys, ModifierKeys.None)
        End Sub
        
        #Region "Properties"
        Public Overridable ReadOnly Property TestAddTimedTaskParams() As TestAddTimedTaskParams
            Get
                If (Me.mTestAddTimedTaskParams Is Nothing) Then
                    Me.mTestAddTimedTaskParams = New TestAddTimedTaskParams()
                End If
                Return Me.mTestAddTimedTaskParams
            End Get
        End Property
        
        Public ReadOnly Property UIItem4getWindow() As UIItem4getWindow
            Get
                If (Me.mUIItem4getWindow Is Nothing) Then
                    Me.mUIItem4getWindow = New UIItem4getWindow()
                End If
                Return Me.mUIItem4getWindow
            End Get
        End Property
        #End Region
        
        #Region "Fields"
        Private mTestAddTimedTaskParams As TestAddTimedTaskParams
        
        Private mUIItem4getWindow As UIItem4getWindow
        #End Region
    End Class
    
    '''<summary>
    '''Parameters to be passed into 'TestAddTimedTask'
    '''</summary>
    <GeneratedCode("Coded UITest Builder", "11.0.60315.1")>  _
    Public Class TestAddTimedTaskParams
        
        #Region "Fields"
        '''<summary>
        '''Type 'add tuition ,at crown centre ,from 1900 ,to 2100 ,!' in 'textboxInput' text box
        '''</summary>
        Public UITextboxInputEditText As String = "add tuition ,at crown centre ,from 1900 ,to 2100 ,!"
        
        '''<summary>
        '''Type '{Enter}' in 'textboxInput' text box
        '''</summary>
        Public UITextboxInputEditSendKeys As String = "{Enter}"
        #End Region
    End Class
    
    <GeneratedCode("Coded UITest Builder", "11.0.60315.1")>  _
    Public Class UIItem4getWindow
        Inherits WinWindow
        
        Public Sub New()
            MyBase.New
            Me.SearchProperties(WinWindow.PropertyNames.Name) = "4get"
            Me.SearchProperties.Add(New PropertyExpression(WinWindow.PropertyNames.ClassName, "WindowsForms10.Window", PropertyExpressionOperator.Contains))
            Me.WindowTitles.Add("4get")
        End Sub
        
        #Region "Properties"
        Public ReadOnly Property UIEnterCommandHereWindow() As UIEnterCommandHereWindow
            Get
                If (Me.mUIEnterCommandHereWindow Is Nothing) Then
                    Me.mUIEnterCommandHereWindow = New UIEnterCommandHereWindow(Me)
                End If
                Return Me.mUIEnterCommandHereWindow
            End Get
        End Property
        #End Region
        
        #Region "Fields"
        Private mUIEnterCommandHereWindow As UIEnterCommandHereWindow
        #End Region
    End Class
    
    <GeneratedCode("Coded UITest Builder", "11.0.60315.1")>  _
    Public Class UIEnterCommandHereWindow
        Inherits WinWindow
        
        Public Sub New(ByVal searchLimitContainer As UITestControl)
            MyBase.New(searchLimitContainer)
            Me.SearchProperties(WinWindow.PropertyNames.ControlName) = "textboxInput"
            Me.WindowTitles.Add("4get")
        End Sub
        
        #Region "Properties"
        Public ReadOnly Property UITextboxInputEdit() As WinEdit
            Get
                If (Me.mUITextboxInputEdit Is Nothing) Then
                    Me.mUITextboxInputEdit = New WinEdit(Me)
                    Me.mUITextboxInputEdit.WindowTitles.Add("4get")
                End If
                Return Me.mUITextboxInputEdit
            End Get
        End Property
        #End Region
        
        #Region "Fields"
        Private mUITextboxInputEdit As WinEdit
        #End Region
    End Class
End Namespace