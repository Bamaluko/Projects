<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" encoding="UTF-8"/>

	<xsl:template match="/">
		<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html&gt;</xsl:text>
		<html xmlns="http://www.w3.org/1999/xhtml">
			<head>
				<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
				<title>Music Colection</title>
			</head>
			<body style="font-family:TimesNewRoman;font-size:14px;">
				<table style="border: 1px solid black; border-collapse: collapse;width:100%">
					<tr>
						<th>ID</th>
						<th>Tytul</th>
						<th>Wykonawca</th>
						<th>RokWydania</th>
						<th>Dlugosc</th>
					</tr>
					<xsl:for-each select="Transformacja/Plyty/Plyta">
						<tr>
							<td>
								<xsl:value-of select="@ID" />
							</td>
							<td>
								<xsl:value-of select="Tytul" />
							</td>
							<td>
								<xsl:value-of select="Wykonawca"/>
							</td>
							<td>
								<xsl:value-of select="RokWydania" />
							</td>
							<td>
								<xsl:value-of select="Dlugosc" />
							</td>
						</tr>
					</xsl:for-each>
				</table>
				<h2>
					Autor: <xsl:value-of select="Transformacja/Report/Autor"/>
				</h2>
				<h2>
					Ilosc sal: <xsl:value-of select="Transformacja/Report/IloscSal"/>
				</h2>
				<h2>
					Ilosc dzialow: <xsl:value-of select="Transformacja/Report/IloscDzialow"/>
				</h2>
				<h2>
					Ilosc plyt: <xsl:value-of select="Transformacja/Report/IloscPlyt"/>
				</h2>
				<h2>
					Data wykonania raportu: <xsl:value-of select="Transformacja/Report/DataWygenerowaniaRaportu"/>
				</h2>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>