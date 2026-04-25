---
layout: single
title: "Matthew Freeman"
---

## Recent Projects

{% assign all_projects = site.projectsgis | concat: site.projectsarduino | sort: "date" | reverse %}

{% for project in all_projects limit: 5 %}
- **[{{ project.title }}]({{ project.url }})**  
  {{ project.excerpt }}
{% endfor %}
