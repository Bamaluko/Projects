<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:fo="http://www.w3.org/1999/XSL/Format">
	<xsl:output method="text" encoding="UTF-8" />

	<xsl:template match="Transformacja/Plyty">
		<xsl:text>&#xA;ID&#09; | TYTUL&#09; | WYKONAWCA&#09; | ROK_WYDANIA&#xA;</xsl:text>
		<xsl:for-each select="Plyta">
			<xsl:sort select="@ID" />
			<xsl:value-of select="@ID"></xsl:value-of>
			<xsl:text> | &#09;</xsl:text>
			<xsl:value-of select="Tytul"></xsl:value-of>
			<xsl:text> | &#09;</xsl:text>
			<xsl:value-of select="Wykonawca"></xsl:value-of>
			<xsl:text> | &#09;</xsl:text>
			<xsl:value-of select="RokWydania"></xsl:value-of>
			<xsl:text>&#xA;</xsl:text>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="Transformacja/Report">
		<xsl:text>Raport&#xA;</xsl:text>
		<xsl:text>&#xA;</xsl:text>
		
		<xsl:text>Autor:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="Autor"/>
		<xsl:text>&#xA;</xsl:text>
		
		<xsl:text>Ilosc sal:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscSal"/>
		<xsl:text>&#xA;</xsl:text>
		
		<xsl:text>Liczba dzialow:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscDzialow"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Liczba plyt:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscPlyt"/>
		<xsl:text>&#xA;</xsl:text>
		
		<xsl:text>Liczba plyt rockowych:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscPlytRock"/>
		<xsl:text>&#xA;</xsl:text>
		
		<xsl:text>Udzial rocka w calosci:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="UdzialRockaWCalosci"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Liczba plyt jazzowcyh:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscPlytJazz"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Udzial jazzu w calosci:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="UdzialJazzuWCalosci"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Liczba plyt popowych:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscPlytPop"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Udzial popu w calosci:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="UdzialPopuWCalosci"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Liczba plyt z metalem:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="IloscPlytMetal"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>Udzial metalu w calosci:&#x09;&#x09;</xsl:text>
		<xsl:value-of select="UdzialMetaluWCalosci"/>
		<xsl:text>&#xA;</xsl:text>
	</xsl:template>

	

</xsl:stylesheet>