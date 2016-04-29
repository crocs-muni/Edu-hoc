<%-- 
    Document   : DisplayScenarioStatus
    Created on : 29.4.2016, 15:48:04
    Author     : lukemcnemee
--%>
<%@ page import="configuration.S01"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Scenarios Status</title>
    </head>
    <body>
        <h1>Scenarios Status</h1>
        <%
            S01 scenario = new S01();
            scenario.run();

            out.print(scenario.displayStatus());
        %>
        This scenario Seed is:
        <%
            out.print(scenario.displaySeed());
        %>
    </body>
</html>
