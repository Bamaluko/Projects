<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" encoding="UTF-8" />
	<xsl:template match="/PLYTOTEKA_CD">

		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="pl" lang="pl">

			<head>
				<center>
					<title>PŁYTOTEKA</title>
				</center>
			</head>

			<body>
				<h1>
					<xsl:value-of select="NAGLOWEK/NAZWA_PROJEKTU"/>
				</h1>
				<h2>
					Autor: <xsl:value-of select="NAGLOWEK/AUTOR/@Imie_i_nazwisko"/>
				</h2>

				<xsl:for-each select="SALE/SALA">
					<xsl:for-each select="DZIAL">
						<h3>
							<xsl:value-of select="@nazwa_gatunku"/>
						</h3>
						<h3>
							Plyt w dziale: 
							<xsl:value-of select="count(PLYTA)"/>
						</h3>
						<table border="1">
							<tr bgcolor="#9acd32">
								<th>Id plyty</th>
								<th>Wykonawca</th>
								<th>Tytul</th>
								<th>Dlugosc</th>
								<th>Rok wydania</th>
								<th>Typ</th>
							</tr>
							<xsl:for-each select="PLYTA">
								<xsl:sort select="WYKONAWCA" order="ascending"/>
								<tr>
									<td>
										<xsl:value-of select="@Id_plyty"/>
									</td>
									<td>
										<xsl:value-of select="WYKONAWCA"/>
									</td>
									<td>
										<xsl:value-of select="TYTUL"/>
									</td>
									<td>
										<xsl:value-of select="DLUGOSC/@Dlugosc"/>
									</td>
									<td>
										<xsl:value-of select="ROK_WYDANIA"/>
									</td>
									<td>
										<xsl:choose>
											<xsl:when test="1970 >= ROK_WYDANIA">
												<b>Klasyk</b>
											</xsl:when>
											<xsl:when test="2000 >= ROK_WYDANIA">
												<b>Poprzednie Milenium</b>
											</xsl:when>
											<xsl:otherwise>
												<b>Nowe Milenium</b>
											</xsl:otherwise>	
										</xsl:choose>
									</td>
								</tr>
							</xsl:for-each>
						</table>
					</xsl:for-each>
				</xsl:for-each>
			</body>

		</html>

	</xsl:template>

</xsl:stylesheet>