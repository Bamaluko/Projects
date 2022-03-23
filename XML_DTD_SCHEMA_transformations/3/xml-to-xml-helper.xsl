<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="2.0">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent ="yes"/>
	<xsl:template match="/">
		<xsl:element name="Transformacja">
			<xsl:element name="Report">
				<xsl:element name = "Autor">
					<xsl:value-of select="PLYTOTEKA_CD/NAGLOWEK/AUTOR/@Imie_i_nazwisko"/>
				</xsl:element>
				<xsl:element name="IloscSal">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA)"/>
				</xsl:element>
				<xsl:element name="IloscDzialow">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL)"/>
				</xsl:element>
				
				<xsl:element name="IloscPlyt">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA)"/>
				</xsl:element>
				
				<xsl:element name="IloscPlytRock">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Rock']/PLYTA)"/>
				</xsl:element>
				<xsl:element name="UdzialRockaWCalosci">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Rock']/PLYTA) div count(PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA)"/>
				</xsl:element>
				
				<xsl:element name="IloscPlytJazz">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Jazz']/PLYTA)"/>
				</xsl:element>
				<xsl:element name="UdzialJazzuWCalosci">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Jazz']/PLYTA) div count(PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA)"/>
				</xsl:element>
				
				<xsl:element name="IloscPlytPop">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Pop']/PLYTA)"/>
				</xsl:element>
				<xsl:element name="UdzialPopuWCalosci">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Pop']/PLYTA) div count(PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA)"/>
				</xsl:element>
				
				<xsl:element name="IloscPlytMetal">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Metal']/PLYTA)"/>
				</xsl:element>
				<xsl:element name="UdzialMetaluWCalosci">
					<xsl:value-of select="count(PLYTOTEKA_CD/SALE/SALA/DZIAL[@nazwa_gatunku = 'Metal']/PLYTA) div count(PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA)"/>
				</xsl:element>
				
				<xsl:element name="DataWygenerowaniaRaportu">
					<xsl:value-of  select="current-dateTime()"/>
				</xsl:element>
			</xsl:element>
			<xsl:element name="Plyty">
				<xsl:for-each select="PLYTOTEKA_CD/SALE/SALA/DZIAL/PLYTA">
					<xsl:element name="Plyta">
						<xsl:attribute name="ID">
							<xsl:value-of select="@Id_plyty"/>
						</xsl:attribute>
						<xsl:element name="Tytul">
							<xsl:value-of select="TYTUL"/>
						</xsl:element>
						<xsl:element name="Wykonawca">
							<xsl:value-of select="WYKONAWCA"/>
						</xsl:element>
						<xsl:element name="RokWydania">
							<xsl:value-of select="ROK_WYDANIA"/>
						</xsl:element>
						<xsl:element name="Dlugosc">
							<xsl:value-of select="DLUGOSC/@Dlugosc"/>
						</xsl:element>
					</xsl:element>
				</xsl:for-each>
			</xsl:element>
		</xsl:element>
	</xsl:template>
	
	
</xsl:stylesheet>