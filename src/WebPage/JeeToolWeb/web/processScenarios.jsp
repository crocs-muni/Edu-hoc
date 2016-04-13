<%-- 
    Document   : processScenarios
    Created on : 13.4.2016, 22:59:23
    Author     : lukemcnemee
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Reading Scenario Selections</title>
    </head>
    <body>
    <center>
        <h1>Scenario Selections</h1>
        <ul>
            <li><p><b>01:</b>
                        <%= request.getParameter("01")%>
                </p></li>
            <li><p><b>02:</b>
                        <%= request.getParameter("02")%>
                </p></li>
            <li><p><b>03:</b>
                        <%= request.getParameter("03")%>
                </p></li>
            <li><p><b>04:</b>
                        <%= request.getParameter("04")%>
                </p></li>
            <li><p><b>05:</b>
                        <%= request.getParameter("05")%>
                </p></li>
        </ul>
    </body>
</html>